#include "Board.h"
#include"GameObject.h"
#include"Device.h"

#include <stdlib.h>
#include<Windows.h>
#include<iostream>


Board::Board()
	:gameOver(true)
	, next(0)
	, m_pDevice(nullptr)
	, m_pDeviceContext(nullptr)
	, m_pSwapChain(nullptr)
{
	InitStage();
	block = new Block();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			boardColor[y][x] = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}


}


Board::~Board()
{
	delete block;

	m_pDevice->Release();
	m_pDeviceContext->Release();
	m_pSwapChain->Release();

}

void Board::InitStage()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y == height - 1)
			{
				stage[y][x] = OBJ_WALL;
			}
			else if (x == 0 || x == width - 1)
			{
				stage[y][x] = OBJ_WALL;
			}
			else
			{
				stage[y][x] = OBJ_SPACE;
			}
		}
	}
}

void Board::ShowNewBoard(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{

	MakeBoard();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (stage[y][x] == OBJ_BLOCK || stage[y][x] == OBJ_WALL)
			{
				MakeBlock(device, x, y);

			}
			else if (board[y][x] == OBJ_BLOCK)
			{
				MakeFallBlock(device, x, y, x - blockPlace.x, y - blockPlace.y);
			}

		}
	}

	Render(device, m_View, m_Proj);
}

void Board::ShowBoard(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{

	MakeBoard();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (stage[y][x] == OBJ_BLOCK || stage[y][x] == OBJ_WALL)
			{

			}
			else if (board[y][x] == OBJ_BLOCK)
			{
				MakeFallBlock(device, x, y, x - blockPlace.x, y - blockPlace.y);
			}

		}
	}

	Render(device, m_View, m_Proj);
}


void Board::CreateBlock()
{
	int num = next;

	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			m_block[y][x] = block->blocks[num][y][x];
		}
	}

	color = DirectX::XMFLOAT4(block->Colors[num].x, block->Colors[num].y, block->Colors[num].z, block->Colors[num].w);

	blockPlace.x = width / 2 - 2;
	blockPlace.y = 0;

	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				if (!Check(y + blockPlace.y, x + blockPlace.x))
				{
					gameOver = false;
					break;

				}
			}
		}
	}

	next = GetRandom(0, blockNum - 1);

}

void Board::SetBlock()
{
	//MakeBoard();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			stage[y][x] = board[y][x];

		}
	}

}

void Board::MakeBoard()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			board[y][x] = stage[y][x];

		}
	}

	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			board[y + blockPlace.y][x + blockPlace.x] = (Type)((int)m_block[y][x] + (int)board[y + blockPlace.y][x + blockPlace.x]);

		}
	}

}

void Board::FallBlock(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{
	blockPlace.y++;
	for (GameObject* oinusama : fallBlock)
	{
		oinusama->addMove(0.0f, -0.1f, 0.0f);
	}
}

void Board::MoveRight()
{

	if (CheckRight())
	{
		blockPlace.x++;
		for (GameObject* oinusama : fallBlock)
		{
			oinusama->addMove(0.1f, 0.0f, 0.0f);
		}
	}


}

void Board::MoveLeft()
{

	if (CheckLeft())
	{
		blockPlace.x--;
		for (GameObject* oinusama : fallBlock)
		{
			oinusama->addMove(-0.1f, 0.0f, 0.0f);
		}
	}


}


void Board::Rotate(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{
	MakeRotateBlock();
	if (CheckRotate())
	{
		for (int y = 0; y < blockHeight; y++)
		{
			for (int x = 0; x < blockWidth; x++)
			{
				m_block[y][x] = rotateBlock[y][x];
			}
		}
		for (GameObject* oinusama : fallBlock)
		{
			oinusama->addMove(0.0f, 0.0f, (3.14159/2));

		}
	}
}

int Board::CheckLine()
{
	for (int y = 0; y < height - 1; y++)
	{
		bool flag = true;
		for (int x = 1; x < width - 1; x++)
		{
			if (stage[y][x] == OBJ_SPACE)
			{
				flag = false;
			}
		}
		if (flag == true)
		{
			return y;
		}
	}
	return -1;
}

void Board::DeleteLine(int line)
{
	for (int y = line; y > 0; y--)
	{
		for (int x = 1; x < width - 1; x++)
		{
			stage[y][x] = stage[y - 1][x];
		}
	}
	for (int x = 1; x < width - 1; x++)
	{
		stage[0][x] = OBJ_SPACE;
	}
}


bool Board::CheckLeft()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				if (!Check(y + blockPlace.y, x + blockPlace.x - 1))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::CheckRight()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				if (!Check(y + blockPlace.y, x + blockPlace.x + 1))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::CheckBottom()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				if (!Check(y + blockPlace.y + 1, x + blockPlace.x))
				{
					return false;
				}
			}
		}
	}
	return true;

}

bool Board::CheckRotate()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (rotateBlock[y][x] == OBJ_BLOCK)
			{
				if (!Check(y + blockPlace.y, x + blockPlace.x))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::Check(int stage_y, int stage_x)
{
	if (stage[stage_y][stage_x] == OBJ_BLOCK || stage[stage_y][stage_x] == OBJ_WALL)
	{
		return false;
	}
	return true;

}

void Board::DeleteAllLine()
{
	while (true)
	{
		int line = CheckLine();
		if (line == -1)
		{
			break;
		}
		else
		{
			DeleteLine(line);
		}
	}
}

int Board::GetRandom(int min, int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

void Board::MakeRotateBlock()
{
	InitRotateBlock();

	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				rotateBlock[x][-y + 4 - 1] = OBJ_BLOCK;
			}
		}
	}

}

void Board::InitRotateBlock()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			rotateBlock[y][x] = OBJ_SPACE;
		}

	}
}

void Board::MakeBlock(Device* device, int x, int y)
{
	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);

	GameObject* oinusama = new GameObject();
	if (boardColor[y][x].x != 0.0f || boardColor[y][x].y != 0.0f || boardColor[y][x].z != 0.0f)
	{
		oinusama->Init(m_pDevice, m_pDeviceContext, L"img.png", x, y, boardColor[y][x]);
	}
	else
	{
		oinusama->Init(m_pDevice, m_pDeviceContext, L"img.png", x, y, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//oinusama->Init(m_pDevice, m_pDeviceContext, x, y, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	blocks.push_back(oinusama);


}

void Board::MakeFallBlock(Device* device, int x, int y, int block_x, int block_y)
{
	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);

	GameObject* oinusama = new GameObject();
	oinusama->Init(m_pDevice, m_pDeviceContext, L"img.png", x, y, color);
	oinusama->SetCenter(block_x, block_y);
	fallBlock.push_back(oinusama);


}

void Board::DeleteGameObject()
{
	for (GameObject* oinusama : blocks)
	{
		delete oinusama;

	}
	for (GameObject* oinusama : fallBlock)
	{
		delete oinusama;
	}
	blocks.clear();
	fallBlock.clear();

}

void Board::DeleteFallBlock()
{
	for (GameObject* oinusama : fallBlock)
	{
		delete oinusama;
	}
	fallBlock.clear();
}

void Board::Render(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{
	device->Begin();

	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);

	for (GameObject* oinusama : blocks)
	{
		oinusama->Render(m_pDeviceContext, m_View, m_Proj);
	}
	for (GameObject* oinusama : fallBlock)
	{

		oinusama->Render(m_pDeviceContext, m_View, m_Proj);
	}
	for (GameObject* oinusama : nextBlock)
	{
		oinusama->Render2(m_pDeviceContext, m_View, m_Proj);
	}

	device->GetSwapChain(&m_pSwapChain);
	m_pSwapChain->Present(0, 0);


}

void Board::SetColor()
{
	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (m_block[y][x] == OBJ_BLOCK)
			{
				boardColor[blockPlace.y + y][blockPlace.x + x] = color;
			}

		}
	}
}

void Board::CreateNextBlock(Device* device)
{
	for (GameObject* block : nextBlock)
	{
		delete block;
	}
	nextBlock.clear();

	for (int y = 0; y < blockHeight; y++)
	{
		for (int x = 0; x < blockWidth; x++)
		{
			if (block->blocks[next][y][x] == OBJ_BLOCK)
			{
				GameObject* oinusama = new GameObject();
				device->GetDevice(&m_pDevice);
				device->GetDeviceContext(&m_pDeviceContext);
				oinusama->Init(m_pDevice, m_pDeviceContext, L"img.png", x + 10, y - 4, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
				blocks.push_back(oinusama);
			}

		}
	}


}