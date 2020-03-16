#include "Scene.h"
#include"Device.h"
#include"Material.h"


#include<Windows.h>


Scene::Scene()
	:m_pDevice(nullptr),
	m_pDeviceContext(nullptr)
{
}

Scene::~Scene()
{
	if (m_pDevice)
	{
		m_pDevice->Release();

	}

	if (m_pDeviceContext)
	{
		m_pDeviceContext->Release();

	}
	
}


void Scene::Init(Device* device, const FLOAT aspectRatio)
{
}

bool Scene::Update(Device* device)
{
	return true;
}







