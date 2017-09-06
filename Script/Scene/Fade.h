#pragma once

#include "..\..\Lib\Script.h"

class Fade : public Script
{
public:
	Fade(void) : Script("Fade") {};

	// ÉVÅ[Éì
	virtual void FadeIn(Scene * _this);
	virtual void FadeOut(Scene * _this);
} scr;