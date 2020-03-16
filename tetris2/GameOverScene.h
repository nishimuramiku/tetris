#pragma once
#include "Scene.h"
class GameOverScene :
	public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	void Init(Device* device, const FLOAT aspectRatio);

	bool Update(Device* device);

private:
	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Proj;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
};

