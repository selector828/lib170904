#pragma once

#include "Window.h"
#include "DirectX.h"
#include "Texture.h"
#include "Scene.h"

class Game
{
public:
	static Game & Instance(void)
	{
		static Game game;
		return game;
	}
private:
	map<string, Scene> Scenes;
public:
	// 初期化
	void Init(void)
	{
		Window::Instance();
		DirectX::Instance();
		Texture::Instance()->Load(TEX_DIR".png", TEX_DIR".tex");
		this->LoadScenes();
	};
	// メインループ
	void Update(void)
	{
		while (DirectX::Instance()->Update())
		{
			if (Scene::SceneState() == scene_state::Init)
			{
				this->Scenes[Scene::CurrentScene()].Init();
				Scene::SceneState() = scene_state::FadeIn;
				Scene::CurrentFadeTime() = Scene::FadeTime();
			}
			if (Scene::SceneState() == scene_state::FadeIn)
			{
				if (Scene::CurrentFadeTime())
				{
					this->Scenes[Scene::CurrentScene()].FadeIn();
					Scene::CurrentFadeTime()--;
				}
				else
				{
					Scene::SceneState() = scene_state::Update;
				}
			}
			else if (Scene::SceneState() == scene_state::Update)
			{
				this->Scenes[Scene::CurrentScene()].Update();
				this->Scenes[Scene::CurrentScene()].LateUpdate();
			}
			else if (Scene::SceneState() == scene_state::FadeOut)
			{
				if (Scene::CurrentFadeTime())
				{
					this->Scenes[Scene::CurrentScene()].FadeOut();
					Scene::CurrentFadeTime()--;
				}
				else
				{
					Scene::SceneState() = scene_state::Uninit;
				}
			}
			if (Scene::SceneState() == scene_state::Uninit)
			{
				this->Scenes[Scene::CurrentScene()].Uninit();
				Scene::CurrentScene() = Scene::NextScene();
				Scene::SceneState() = scene_state::Init;
			}

			this->Scenes[Scene::CurrentScene()].Draw();
		}
	};
	// 終了
	void Uninit(void)
	{
		DirectX::Instance()->Uninit();
	};

	void LoadScenes(void)
	{
		vector<string> fileNames = this->get_file_path_in_dir("/Scene", "Scene");

		for (auto & name : fileNames)
			this->Scenes[name] = Scene(name);
	}

	vector<string> get_file_path_in_dir(const string& dir_name, const string& extension) noexcept(false)
	{
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;//defined at Windwos.h
		vector<string> file_names;
		
		//拡張子の設定
		char c[255];
		GetCurrentDirectory(255, c);
		string search_name = string(c) + dir_name + "\\*." + extension;

		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) {
			throw runtime_error("file not found");
		}

		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			}
			else {
				string str = win32fd.cFileName;
				string sub = str.substr(0, strlen(str.c_str()) - strlen(extension.c_str()) - 1);
				file_names.push_back(sub);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);

		return file_names;
	}
};