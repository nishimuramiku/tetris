#pragma once


class Scene;
class Device;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	enum SCENE
	{
		TITLE,
		GAME,
		GAMEOVER,

	};

	void ChangeScene(SCENE scene);
	bool Update(Device* device);
	bool Init(Device* device, float aspectRatio);

private:
	Scene* currentScene;
};

