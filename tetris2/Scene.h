#pragma once
#include<DirectXmath.h>
#include<d3d11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

class Device;

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Init(Device* device, const FLOAT aspectRatio) = 0;
	virtual bool Update(Device* device) = 0;


private:

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;



};
