#pragma once

#include<DirectXmath.h>
#include<vector>
#include<d3d11.h>

#include"Block.h"

class Block;
class GameObject;
class Device;



struct place
{
	int x;
	int y;
};



class Board
{


public:
	Board();
	~Board();

	void ShowNewBoard(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);
	void ShowBoard(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);
	void CreateBlock();
	void CreateNextBlock(Device* device);
	void SetBlock();
	void FallBlock(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);
	void DeleteAllLine();

	void MoveRight();
	void MoveLeft();
	void Rotate(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);

	bool CheckBottom();

	bool GameOver()
	{
		return gameOver;
	}

	void Render(Device* device, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);
	void DeleteGameObject();
	void DeleteFallBlock();

	void SetColor();
	
	void MakeBoard();


private:
	static constexpr int height = 18;
	static constexpr int width = 14;
	static constexpr int blockHeight = 4;
	static constexpr int blockWidth = 4;
	static constexpr int blockNum = 4;

	bool gameOver;
	int next;

	Block* block;

	Type board[height][width];
	Type stage[height][width];
	Type rotateBlock[blockHeight][blockWidth];
	Type m_block[blockHeight][blockWidth];

	DirectX::XMFLOAT4 boardColor[height][width];

	place blockPlace;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;

	std::vector<GameObject*> blocks;
	std::vector<GameObject*> fallBlock;
	std::vector<GameObject*> nextBlock;

	


private:
	void InitStage();
	
	bool CheckLeft();
	bool CheckRight();
	bool CheckRotate();
	bool Check(int stage_y, int stage_x);
	int CheckLine();
	void DeleteLine(int line);
	int GetRandom(int min, int max);
	void MakeRotateBlock();
	void InitRotateBlock();

	void MakeBlock(Device* device, int x, int y);
	void MakeFallBlock(Device* device,int x, int y, int block_x, int block_y);

	DirectX::XMFLOAT4 color;

	




};