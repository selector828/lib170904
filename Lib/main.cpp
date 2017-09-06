#include "Game.h"

int WINAPI WinMain(WIN_PARAM)
{
	Game::Instance().Init();
	Game::Instance().Update();
	Game::Instance().Uninit();
}