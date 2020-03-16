#pragma once
#include "Scene.h"

class Board;


class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();

	bool Update(Device* device);
	void Init(Device* device, const FLOAT aspectRatio);


private:
	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Proj;
	
	bool fallFlag;
	int timer;

	Board* board;

private:

	void MoveJudge(Device* device, Board* board);

	bool GetFallFlag()
	{
		return fallFlag;
	}
	int GetTimer()
	{
		return timer;
	}
	void AddTime()
	{
		timer++;
	}
	void FlagOff()
	{
		fallFlag = false;
	}

};

