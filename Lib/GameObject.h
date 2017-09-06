#pragma once

#include "Script.h"
#include <vector>
#include <string>
#include <fstream>

#define OBJ_DIR  "GameObject\\"
#define OBJ_FILE ".GameObject"

class GameObject
{
	// コンストラクタ・デストラクタ
public:
	GameObject(void) {};
	GameObject(string name)
	{
		this->LoadFromFile(OBJ_DIR + name + OBJ_FILE);
	};
	virtual ~GameObject(void)
	{
		this->Scripts.clear();
		this->Childs.clear();
	};
public:
	// 親子
private: //隠蔽
	GameObject * Parent = nullptr;
	vector<GameObject*> Childs = {};
public:
	GameObject * GetParent(void) { return this->Parent; };
	void SetParent(GameObject * parent) { this->Parent = parent; };
	vector<GameObject*> GetChilds(void) { return this->Childs; };
	void AddChild(GameObject * child)
	{
		child->SetParent(this);
		this->Childs.push_back(child);
	};
	void RemoveChild(GameObject * child)
	{
		for (unsigned int n = 0; n < this->Childs.size(); n++)
			if (this->Childs[n] == child)
				this->Childs.erase(this->Childs.begin() + n);
	};
	// パラメーター
private: // 隠蔽
	map<string, int> IntParam = {};
	map<string, float> FloatParam = {};
	map<string, string> StringParam = {};
	map<string, GameObject*> pParam = {};
public: // ゲッター
	template<class G>
	G GetParam(string key) {};

	template<>int GetParam(string key) { return this->IntParam[key]; };
	template<>float GetParam(string key) { return this->FloatParam[key]; };
	template<>string GetParam(string key) { return this->StringParam[key]; };
	template<>GameObject * GetParam(string key) { return this->pParam[key]; };
public: // セッター
	template<class S>
	void SetParam(string key, S value) {};

	template<>void SetParam(string key, int value) { this->IntParam[key] = value; };
	template<>void SetParam(string key, float value) { this->FloatParam[key] = value; };
	template<>void SetParam(string key, string value) { this->StringParam[key] = value; };
	template<>void SetParam(string key, const char * value) { this->StringParam[key] = value; };
	template<>void SetParam(string key, char * value) { this->StringParam[key] = value; };
	template<>void SetParam(string key, GameObject * value) { this->pParam[key] = value; };
public: // アップデーター
	template<class U>
	void UpdateParam(string key, U value) {};

	template<>void UpdateParam(string key, int value) { this->IntParam[key] += value; };
	template<>void UpdateParam(string key, float value) { this->FloatParam[key] += value; };
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
	void OnCreate(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->OnCreate(this);
	};
	void Init(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Init(this);
	};
	void FadeIn(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->FadeIn(this);
	};
	void Update(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Update(this);
	};
	void LateUpdate(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->LateUpdate(this);
	};
	void FadeOut(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->FadeOut(this);
	};
	void Pause(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Pause(this);
	};
	void Draw(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Draw(this);
	};
	void Uninit(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->Uninit(this);
	};
	void OnDestroy(void)
	{
		for (auto & script : Scripts)
			if (Script::Scripts()[script] != nullptr)
				Script::Scripts()[script]->OnDestroy(this);
	};
	
	void LoadFromFile(string filePath)
	{
		ifstream ifs(filePath);

		if (ifs.fail())
		{
			printf("GameObjectファイルが見つかりませんでした。");
			Window::CloseWindow();
		}
		string str;
		while (getline(ifs, str))
		{
			this->AddScript(str);
		}
	}
};