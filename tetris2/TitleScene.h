#pragma once
#include "Scene.h"


class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init(Device* device,float aspectRatio);
	bool Update(Device* device);

private:
	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Proj;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
};

