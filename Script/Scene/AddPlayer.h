#pragma once

#include "..\..\Lib\Script.h"

class AddPlayer : public Script
{
public:
	AddPlayer(void) : Script("AddPlayer") {};

	// ÉVÅ[Éì
	void Init(Scene * _this) override;
	virtual void FadeIn(Scene * _this) {};
	virtual void Update(Scene * _this) {};
	virtual void LateUpdate(Scene * _this) {};
	virtual void FadeOut(Scene * _this) {};
	virtual void Pause(Scene * _this) {};
	virtual void Draw(Scene * _this) {};
	virtual void Uninit(Scene * _this) {};
} scr;