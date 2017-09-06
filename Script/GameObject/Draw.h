#pragma once
#include "..\..\Lib\Script.h"

class DrawScript : public Script
{
public:
	DrawScript(void) : Script("Draw") {};
	void Init(GameObject * _this) override;
	void Draw(GameObject * _this) override;
};