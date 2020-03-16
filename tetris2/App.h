#pragma once
#pragma comment(lib,"d3d11.lib")

#include<d3d11.h>
#include<d3dcompiler.h>

#include"Window.h"

class Device;
class Scene;
class Board;
class SceneManager;

class App
{
public:
	App();
	~App();

	int Run();

private:
	bool InitApp();
	bool InitD3D11();
	void MainLoop();

	Scene* scene;


private:
	Window* window;
	Device* device;
	SceneManager* sceneManager;
	
	Window::Config config;

	FLOAT m_AspectRatio;



};