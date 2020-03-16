#include "GameScene.h"
#include"Board.h"


GameScene::GameScene()
	:fallFlag(true),
	timer(0)
{
	m_View = DirectX::XMMatrixIdentity();
	m_Proj = DirectX::XMMatrixIdentity();
	board = new Board();
}


GameScene::~GameScene()
{
}

void GameScene::Init(Device* device, const FLOAT aspectRatio)
{
	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -1.5f, 1.0f);
	DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camUpward = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


	m_View = DirectX::XMMatrixLookAtLH(camPos, camTarget, camUpward);
	m_Proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, aspectRatio, 0.01f, 1000.0f);
}

bool GameScene::Update(Device* device)
{
	

	if (GetFallFlag())
	{

		board->CreateBlock();
		board->CreateNextBlock(device);
		board->ShowNewBoard(device, m_View, m_Proj);

		if (!board->GameOver())
		{
			return false;
		}
		FlagOff();
	}

	if (!GetFallFlag())
	{
		MoveJudge(device, board);
	}
	AddTime();
	return true;
}


void GameScene::MoveJudge(Device* device, Board* board)
{
	if (GetKeyState('A') & 0x8000) {
		Sleep(100);
		board->MoveLeft();

	}
	if (GetKeyState('D') & 0x8000) {
		Sleep(100);
		board->MoveRight();

	}
	if (GetKeyState('R') & 0x8000) {
		Sleep(100);
		board->Rotate(device, m_View, m_Proj);

	}
	if (GetKeyState('S') & 0x8000) {
		board->FallBlock(device, m_Proj, m_View);

	}if (timer > 1000)
	{
		board->FallBlock(device, m_Proj, m_View);
		timer = 0;
	}

	board->Render(device, m_View, m_Proj);

	if (!board->CheckBottom())
	{
		board->MakeBoard();
		board->SetBlock();
		board->SetColor();
		board->DeleteAllLine();
		board->DeleteGameObject();
		fallFlag = true;
	}
}

