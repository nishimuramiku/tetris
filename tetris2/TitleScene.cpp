#include "TitleScene.h"
#include "GameObject.h"
#include"Device.h"




TitleScene::TitleScene()
: m_pDevice(nullptr)
, m_pDeviceContext(nullptr)
,m_pSwapChain(nullptr)

{
}


TitleScene::~TitleScene()
{
	m_pDevice->Release();
	m_pDeviceContext->Release();
	m_pSwapChain->Release();
}

void TitleScene::Init(Device* device, float aspectRatio)
{
	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -1.5f, 1.0f);
	DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camUpward = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


	m_View = DirectX::XMMatrixLookAtLH(camPos, camTarget, camUpward);
	m_Proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, aspectRatio, 0.01f, 1000.0f);
}

bool TitleScene::Update(Device* device)
{
	device->Begin();

	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);
	device->GetSwapChain(&m_pSwapChain);

	GameObject* oinusama = new GameObject();
	oinusama->Init(m_pDevice, m_pDeviceContext, L"title.png", 0, 0, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	oinusama->SetScal(10.0f);
	oinusama->addMove(0.6f, -1.0f, 0.0f);
	oinusama->Render(m_pDeviceContext, m_View, m_Proj);
	m_pSwapChain->Present(4, 0);

	return true;
}
