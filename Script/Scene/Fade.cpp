#include "Fade.h"
#include "..\..\Lib\Scene.h"
#include "..\..\Lib\Camera.h"

void Fade::FadeIn(Scene * _this)
{
	Camera::Color().r = 1.f - (float)Scene::CurrentFadeTime() / (float)Scene::FadeTime();
	Camera::Color().g = 1.f - (float)Scene::CurrentFadeTime() / (float)Scene::FadeTime();
	Camera::Color().b = 1.f - (float)Scene::CurrentFadeTime() / (float)Scene::FadeTime();
	Camera::Color().a = 1.f - (float)Scene::CurrentFadeTime() / (float)Scene::FadeTime();
}

void Fade::FadeOut(Scene * _this)
{
	Camera::Color().r = (float)Scene::CurrentFadeTime() / Scene::FadeTime();
	Camera::Color().g = (float)Scene::CurrentFadeTime() / Scene::FadeTime();
	Camera::Color().b = (float)Scene::CurrentFadeTime() / Scene::FadeTime();
	Camera::Color().a = (float)Scene::CurrentFadeTime() / Scene::FadeTime();
}