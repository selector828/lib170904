#pragma once

#include <windows.h> //Windows���C�u����
#include <d3d9.h>    //DirectX
#include <d3dx9.h>   //DirectX
#include <tchar.h>   //tChar
#include <stdio.h>   //���o�̓��C�u����
#include <Xinput.h>  //XInput���C�u����
#include "Input.h"   //���͊֘A
#include "Window.h"
#include <iostream>
#include <algorithm>
#include <vector>

//���C�u�����t�@�C��
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "xinput.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

//�x��
#pragma warning(disable: 4100)
#pragma warning(disable: 4238)
#pragma warning(disable: 4458)
#pragma warning(disable: 4474)
#pragma warning(disable: 4476)
#pragma warning(disable: 4996)

class DirectX final
{
public:
	static DirectX * Instance(void)
	{
		static DirectX $this = {};

		return &$this;
	};
public:
	void Setup(void);
	void SetVtxBuf(void);
	void SetVtxDecl(void);
	void MessageLoop(void);
	void CalcFPS(void);
	bool Update(void);
	void Uninit(void);
public:
	float _FPS(void) { return this->FPS; };
	LPDIRECT3DDEVICE9            pDevice;
	LPD3DXEFFECT                 pEffect;
	D3DXMATRIX                   Proj;

private:
	LPDIRECT3DVERTEXDECLARATION9 pVtxDecl;
	LPDIRECT3DVERTEXBUFFER9      pVtxBuf;
	D3DXMATRIX                   World;
	float                        FPS;
private:
	DirectX(void);
};