#pragma once
#include "DirectX.h"
#include <map>

using namespace std;

class Scene;
class GameObject;
class Script
{
public:
	Script(string key) {
		Script::Scripts()[key] = this;
		this->_key = key;
	};
	virtual ~Script(void) { Script::Scripts().erase(this->_key); };
private:
	string _key;
public:
	static map<string, Script*> & Scripts(void)
	{
		static map<string, Script*> scripts = {};
		return scripts;
	};
public:
	// シーン
	virtual void Init(Scene * _this) {};
	virtual void FadeIn(Scene * _this) {};
	virtual void Update(Scene * _this) {};
	virtual void LateUpdate(Scene * _this) {};
	virtual void FadeOut(Scene * _this) {};
	virtual void Pause(Scene * _this) {};
	virtual void Draw(Scene * _this) {};
	virtual void Uninit(Scene * _this) {};
	// ゲームオブジェクト
	virtual void OnCreate(GameObject * _this) {};
	virtual void Init(GameObject * _this) {};
	virtual void FadeIn(GameObject * _this) {};
	virtual void Update(GameObject * _this) {};
	virtual void LateUpdate(GameObject * _this) {};
	virtual void FadeOut(GameObject * _this) {};
	virtual void Pause(GameObject * _this) {};
	virtual void Draw(GameObject * _this) {};
	virtual void Uninit(GameObject * _this) {};
	virtual void OnDestroy(GameObject * _this) {};
};