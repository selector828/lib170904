#pragma once

#include "DirectX.h"
#include <map>

#define TEX_DIR "resource/texture/sheet"

class TEXTURE_INFO
{
public:
	D3DXVECTOR2	StartUV;
	D3DXVECTOR2 TextureSize;
	D3DXVECTOR2 Div;
public:
	TEXTURE_INFO(void)
	{
		this->StartUV.x = 0.f;
		this->StartUV.y = 0.f;
		this->TextureSize.x = 1.f;
		this->TextureSize.y = 1.f;
		this->Div.x = 1.f;
		this->Div.y = 1.f;
	}
};

class Texture
{
public:
	std::map<std::string, TEXTURE_INFO> TexturesInfo = {};
	static Texture * Instance(void)
	{
		static Texture $this = {};

		return &$this;
	};
private:
	Texture(void) {};

public:
	static LPDIRECT3DTEXTURE9 GetTexture(void) { return Texture::Instance()->pTexture; };
	static D3DXVECTOR2        GetSize(void) { return Texture::Instance()->Size; };
private:
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXVECTOR2        Size;

public:
	
	void Load(char * FileNameA, char * FileNameB)
	{
		//テクスチャ読込
		D3DXCreateTextureFromFile(DirectX::Instance()->pDevice, FileNameA, &this->pTexture);

		//テクスチャ詳細情報取得
		D3DXIMAGE_INFO dii;
		D3DXGetImageInfoFromFile(FileNameA, &dii);
		this->Size.x = (float)dii.Width;
		this->Size.y = (float)dii.Height;
		
		char map[100];
		int  x = 0;
		int  y = 0;
		int  w = 0;
		int  h = 0;
		int  dx = 0;
		int  dy = 0;

		FILE * fp = nullptr;
		fp = fopen(FileNameB, "r");
		if (fp != nullptr)
		{
			int ret = 0;
			while (ret != EOF)
			{
				ret = fscanf(fp, "%s %d %d %d %d %d %d\n", map, &x, &y, &w, &h, &dx, &dy);
				TexturesInfo[map].StartUV.x = x / this->Size.x;
				TexturesInfo[map].StartUV.y = y / this->Size.y;
				TexturesInfo[map].TextureSize.x = (float)w;
				TexturesInfo[map].TextureSize.y = (float)h;
				TexturesInfo[map].Div.x = (float)dx;
				TexturesInfo[map].Div.y = (float)dy;
			}
		}
		DirectX::Instance()->pEffect->SetTexture("tex", Texture::GetTexture());
	};
};