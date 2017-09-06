#include "AddPlayer.h"
#include "..\..\Lib\Scene.h"

void AddPlayer::Init(Scene * _this)
{
	_this->CreateGameObject("Player", 0.f, 0.f, 0);
}