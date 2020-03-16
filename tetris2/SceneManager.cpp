#include "SceneManager.h"
#include"GameOverScene.h"
#include"TitleScene.h"
#include"GameScene.h"


SceneManager::SceneManager()
	:currentScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	delete currentScene;
}

void SceneManager::ChangeScene(SCENE scene)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}

	switch (scene)
	{
	case SCENE::TITLE:
		currentScene = new TitleScene();
		break;

	case SCENE::GAME:
		currentScene = new GameScene();
		break;

	case SCENE::GAMEOVER:
		currentScene = new GameOverScene();
		break;

	}

}
bool SceneManager::Update(Device* device)
{
	return currentScene->Update(device);
}

bool SceneManager::Init(Device* device,float aspectRatio)
{
	currentScene->Init(device, aspectRatio);
	return true;
}