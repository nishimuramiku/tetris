
#pragma once
#include<DirectXTex.h>
#include<vector>
#include"Block.h"


class Material;
class Mesh;
struct CustomVertex;
struct ConstantBufferForPerFrame;



class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const wchar_t* image,  int x, int y, DirectX::XMFLOAT4 color);
	void SetCenter(int x, int y);
	void Render(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);
	void Render2(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);
	void makeMVP(ConstantBufferForPerFrame* cb,
		float pos_x,
		float pos_y,
		float rot_z, 
		DirectX::XMMATRIX m_View, 
		DirectX::XMMATRIX m_Proj);

	void addMove(float x, float y, float z)
	{
		pos_x += x;
		pos_y += y;
		rot_z += z;
	}

	void SetScal(float s)
	{
		scal = s;
	}


private:

	Material* material;
	Mesh* mesh;

	float pos_x;
	float pos_y;
	float rot_z;
	float scal;

	float m_x;
	float m_y;

	float center_x;
	float center_y;


	D3D11_RASTERIZER_DESC rd;

	ID3D11Buffer* m_pCB;

	static constexpr int height = 18;
	static constexpr int width = 14;

	float dis(int x)
	{
		return (float)(1.5 - x);
	}


};