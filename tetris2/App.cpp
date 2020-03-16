#include "App.h"
#include"Device.h"
#include"Scene.h"
#include"Board.h"
#include"SceneManager.h"

#include<Windows.h>




App::App()
	:window(nullptr),
	device(nullptr),
	scene(nullptr),
	sceneManager(nullptr)
{
	sceneManager = new SceneManager();
}

App::~App()
{
	delete device;
	delete window;
	delete sceneManager;
}

bool App::InitD3D11()
{
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	RECT rc;
	GetClientRect(window->GethWnd(), &rc);

	UINT w = rc.right - rc.left;
	UINT h = rc.bottom - rc.top;
	m_AspectRatio = (FLOAT)w / (FLOAT)h;

	device = new Device(window);

	if (!device->CreateSwapchain())
	{
		return false;
	}

	device->InitDeviceContext();

	return true;
}

bool App::InitApp()
{

	window = new Window(config);

	if (!window->InitWnd())
	{
		return false;
	}
	if (!InitD3D11())
	{
		return false;
	}
	return true;
}


int App::Run()
{

	if (InitApp())
	{
		MainLoop();
	}
	return 0;
}

void App::MainLoop()
{
	
	
	while (true)
	{
		
		MSG msg = { 0 };
		sceneManager->ChangeScene(SceneManager::TITLE);
		sceneManager->Init(device, m_AspectRatio);
		sceneManager->Update(device);
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					break;
					
				}
			}
		}

		sceneManager->ChangeScene(SceneManager::GAME);
		sceneManager->Init(device, m_AspectRatio);
		sceneManager->Update(device);
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				bool flag = sceneManager->Update(device);
				if (!flag)
				{
					break;
				}

			}
		}

		sceneManager->ChangeScene(SceneManager::GAMEOVER);
		sceneManager->Init(device, m_AspectRatio);
		sceneManager->Update(device);
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					break;

				}
			}
		}
		
	}

}




