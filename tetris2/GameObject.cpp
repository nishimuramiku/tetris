#include "GameObject.h"
#include"Material.h"
#include"Mesh.h"


GameObject::GameObject()
	:material(nullptr),
	mesh(nullptr),
	m_pCB(nullptr),
	pos_x(0.0f),
	pos_y(0.0f),
	rot_z(0.0f),
	scal(1.0f),
	center_x(0.0f),
	center_y(0.0f)
{
}


GameObject::~GameObject()
{
	delete material;
	delete mesh;
	
	if (m_pCB)
	{
		m_pCB->Release();
		m_pCB = nullptr;
	}
}

void GameObject::Init(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const wchar_t* image, int x, int y, DirectX::XMFLOAT4 color)
{
	m_x = 0.1f + 0.1 * (x - width / 2);
	m_y = 0.1f - 0.1 * (y - height / 2);
	

	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.CullMode = D3D11_CULL_NONE;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.DepthClipEnable = TRUE;

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(ConstantBufferForPerFrame);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		HRESULT hr = m_pDevice->CreateBuffer(&bd, NULL, &m_pCB);
		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateBuffer() Failed.");
		}
	}

	material = new Material();

	material->createMaterial(
		m_pDevice,
		m_pDeviceContext,
		image,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		rd,
		L"Simple.fx",
		"VSFunc",
		L"Simple.fx",
		"PSFunc");

	

	CustomVertex vertices1[] = {

		{ DirectX::XMFLOAT3(0.05f,0.05f, 0.0f),DirectX::XMFLOAT2(1.0f, 0.0f),color },
		{ DirectX::XMFLOAT3(-0.05f, 0.05f, 0.0f),DirectX::XMFLOAT2(0.0f, 0.0f),color},
		{ DirectX::XMFLOAT3(0.05f, -0.05f, 0.0f),DirectX::XMFLOAT2(1.0f, 1.0f),color},
		{ DirectX::XMFLOAT3(-0.05f, -0.05f, 0.0f),DirectX::XMFLOAT2(0.0f, 1.0f),color },
	};


	mesh = new Mesh();
	mesh->SetVerticesAndCount(vertices1, 4);
	mesh->SetBuffer(m_pDevice, m_pDeviceContext);

}

void GameObject::SetCenter(int x, int y)
{
	center_x = -dis(x);
	center_y = dis(y);
}

void GameObject::Render(
	ID3D11DeviceContext* m_pDeviceContext,
	DirectX::XMMATRIX view,
	DirectX::XMMATRIX proj)
{
	ConstantBufferForPerFrame cb;
	makeMVP(&cb, pos_x, pos_y, rot_z, view, proj);
	m_pDeviceContext->UpdateSubresource(m_pCB, 0, NULL, &cb, 0, 0);
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCB);
	mesh->Render(m_pDeviceContext, view, proj);

}

void GameObject::Render2(
	ID3D11DeviceContext* m_pDeviceContext,
	DirectX::XMMATRIX view,
	DirectX::XMMATRIX proj)
{
	ConstantBufferForPerFrame cb;
	pos_x = 10.0;
	pos_y = 10.0;
	makeMVP(&cb, pos_x, pos_y, rot_z, view, proj);
	m_pDeviceContext->UpdateSubresource(m_pCB, 0, NULL, &cb, 0, 0);
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCB);
	mesh->Render(m_pDeviceContext, view, proj);

}

void GameObject::makeMVP
(ConstantBufferForPerFrame* cb,
	float pos_x, 
	float pos_y, 
	float rot_z,
	DirectX::XMMATRIX m_View,
	DirectX::XMMATRIX m_Proj)
{
	DirectX::XMMATRIX MVP;
	DirectX::XMMATRIX g_matrix;
	DirectX::XMMATRIX t_matrix;
	DirectX::XMFLOAT3 g_pos = { pos_x + m_x , pos_y + m_y , 0 };
	DirectX::XMFLOAT3 g_rot = { 0,0,rot_z };
	DirectX::XMFLOAT3 g_scal = { scal,scal,scal };

	g_matrix = DirectX::XMMatrixIdentity();
	t_matrix = DirectX::XMMatrixIdentity();

	MVP = DirectX::XMMatrixIdentity();


	g_matrix = DirectX::XMMatrixTranslation(0.1 * center_x,0.1 * center_y, 0);

	t_matrix = DirectX::XMMatrixScaling(g_scal.x, g_scal.y, g_scal.z);

	g_matrix *= t_matrix;

	t_matrix = DirectX::XMMatrixRotationRollPitchYaw(g_rot.x, g_rot.y, g_rot.z);

	g_matrix *= t_matrix;

	t_matrix = DirectX::XMMatrixTranslation(g_pos.x -  0.1 * center_x, g_pos.y -  0.1 * center_y, g_pos.z);

	g_matrix *= t_matrix;



	MVP = DirectX::XMMatrixIdentity();
	MVP *= g_matrix;
	MVP *= m_View;
	MVP *= m_Proj;


	cb->world = g_matrix;
	cb->view = m_View;
	cb->proj = m_Proj;
	cb->mvp = MVP;



}
