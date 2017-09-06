#pragma once

#include "DirectX.h"

class Camera
{
public:
	static D3DXCOLOR & Color(void)
	{
		static D3DXCOLOR Color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		return Color;
	};
	static D3DXVECTOR3 & Position(void)
	{
		static D3DXVECTOR3 Position = {};
		return Position;
	};
	static float & Zoom(void)
	{
		static float Zoom = 1.f;
		return Zoom;
	};
};