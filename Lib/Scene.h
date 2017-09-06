#pragma once

#include "GameObject.h"

#define SCENE_DIR  "Scene\\"
#define SCENE_FILE ".Scene"

enum class scene_state
{
	FadeIn,
	Init,
	Update,
	Uninit,
	FadeOut
};

class Scene
{
	// コンストラクタ・デストラクタ
public:
	Scene(void) {};
	Scene(string id) {
		this->LoadFromFile(SCENE_DIR + id + SCENE_FILE);
	};
	virtual ~Scene(void) {};
public:
	static scene_state & SceneState(void)
	{
		static scene_state sceneState = scene_state::Init;
		return sceneState;
	};
	static string & CurrentScene(void)
	{
		static string currentScene = "Game";
		return currentScene;
	};
	static string & NextScene(void)
	{
		static string nextScene = "Game";
		return nextScene;
	};
	static int & FadeTime(void)
	{
		static int fadeTime = 60;
		return fadeTime;
	};
	static int & CurrentFadeTime(void)
	{
		static int currentFadeTime = 60;
		return currentFadeTime;
	};
	// ゲームオブジェクト
private: // 隠蔽
	vector<GameObject*> GameObjects;
public:
	vector<GameObject*> GetGameObjects(void) { return this->GameObjects; };
	GameObject * CreateGameObject(string key, float x = 0.f, float y = 0.f, float z = 0.f)
	{
		this->GameObjects.push_back(new GameObject(key));
		this->GameObjects.back()->SetParam("PositionX", x);
		this->GameObjects.back()->SetParam("PositionY", y);
		this->GameObjects.back()->SetParam("PositionZ", z);
		this->GameObjects.back()->OnCreate();
		return this->GameObjects.back();
	};
	void DestroyGameObject(GameObject * gameObject)
	{
		for (unsigned int n = 0; n < this->GameObjects.size(); n++)
			if (gameObject == this->GameObjects[n])
			{
				gameObject->OnDestroy();
				delete gameObject;
				this->GameObjects.erase(this->GameObjects.begin() + n);
			}
	};

	// スクリプト
private: // 隠蔽
	vector<string> Scripts = {};
public:
	void AddScript(string key) { this->Scripts.push_back(key); };
	void RemoveScript(string key)
	{
		int n = 0;
		for (auto & script : this->Scripts)
		{
			n = 0;
			if (script == key)
				this->Scripts.erase(this->Scripts.begin() + n);
		}
	};
public:
	void Init(void)
	{
		for (auto & script : Scripts)
			if(Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Init(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->Init();
			for (auto & child : gameObject->GetChilds())
				child->Init();
		}
	};
	void FadeIn(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->FadeIn(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->FadeIn();
			for (auto & child : gameObject->GetChilds())
				child->FadeIn();
		}
	};
	void Update(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Update(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->Update();
			for (auto & child : gameObject->GetChilds())
				child->Update();
		}
	};
	void LateUpdate(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->LateUpdate(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->LateUpdate();
			for (auto & child : gameObject->GetChilds())
				child->LateUpdate();
		}
	};
	void FadeOut(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->FadeOut(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->FadeOut();
			for (auto & child : gameObject->GetChilds())
				child->FadeOut();
		}
	};
	void Pause(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Pause(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->Pause();
			for (auto & child : gameObject->GetChilds())
				child->Pause();
		}
	};
	void Draw(void)
	{
		for (auto & script : Scripts)
			if(Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Draw(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->Draw();
			for (auto & child : gameObject->GetChilds())
				child->Draw();
		}
	};
	void Uninit(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Uninit(this);

		for (auto & gameObject : this->GameObjects)
		{
			gameObject->Uninit();
			for (auto & child : gameObject->GetChilds())
				child->Uninit();
		}
	};

	void LoadFromFile(string FilePath)
	{
		ifstream ifs(FilePath);
		string str;
		if (ifs.fail())
		{
			printf("Sceneファイルの読み込みに失敗しました。\n");
			Window::CloseWindow();
		}

		while (getline(ifs, str))
		{
			this->AddScript(str);
		}
	};
};