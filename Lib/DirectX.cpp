#include "DirectX.h"

DirectX::DirectX(void)
{
	this->Setup();
	this->SetVtxBuf();
	this->SetVtxDecl();
}

void DirectX::Setup(void)
{
	LPDIRECT3D9 pD3d;
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return;
	}

	//「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::Instance()->hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &this->pDevice)))
	{
		MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
		return;
	}
	LPD3DXBUFFER pErrMessage = NULL;
	LPCSTR path = "resource/shader/effect01.fx";
	//シェーダファイル読込
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(this->pDevice, path, NULL, NULL,D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, NULL, &this->pEffect, &pErrMessage);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (LPCSTR)(pErrMessage->GetBufferPointer()), "", MB_OK);
		pErrMessage->Release();
		throw 0;
	}
	
	this->SetVtxBuf();
	this->SetVtxDecl();

	// 2D描画用射影変換行列
	D3DXMatrixIdentity(&this->Proj);
	// 射影変換行列作成
	this->Proj._11 = 2.f / SCREEN_WIDTH;
	this->Proj._22 = -2.f / SCREEN_HEIGHT;
	this->Proj._41 = -1.f;
	this->Proj._42 = 1.f;

	SAFE_RELEASE(pD3d);
}

void DirectX::SetVtxBuf(void)
{
	// 共通頂点バッファ作成
	if (this->pVtxBuf == 0) {
		float commonVtx[] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 2
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 3
		};
		this->pDevice->CreateVertexBuffer(sizeof(commonVtx), 0, 0, D3DPOOL_MANAGED, &this->pVtxBuf, 0);
		float *p = 0;
		if (this->pVtxBuf) {
			this->pVtxBuf->Lock(0, 0, (void**)&p, 0);
			memcpy(p, commonVtx, sizeof(commonVtx));
			this->pVtxBuf->Unlock();
		}
	}

	// 頂点バッファ・頂点宣言設定
	this->pDevice->SetStreamSource(0, this->pVtxBuf, 0, sizeof(float) * 5);
}

void DirectX::SetVtxDecl(void)
{
	D3DVERTEXELEMENT9 VtxElem[3];

	// 頂点座標情報の宣言
	VtxElem[0].Stream = 0;
	VtxElem[0].Offset = 0;
	VtxElem[0].Type = D3DDECLTYPE_FLOAT3;
	VtxElem[0].Method = D3DDECLMETHOD_DEFAULT;
	VtxElem[0].Usage = D3DDECLUSAGE_POSITION;
	VtxElem[0].UsageIndex = 0;

	// UV座標情報の宣言
	VtxElem[1].Stream = 0;
	VtxElem[1].Offset = 12;
	VtxElem[1].Type = D3DDECLTYPE_FLOAT2;
	VtxElem[1].Method = D3DDECLMETHOD_DEFAULT;
	VtxElem[1].Usage = D3DDECLUSAGE_TEXCOORD;
	VtxElem[1].UsageIndex = 0;

	// 終端宣言
	VtxElem[2].Stream = 0xFF;
	VtxElem[2].Offset = 0;
	VtxElem[2].Type = D3DDECLTYPE_UNUSED;
	VtxElem[2].Method = 0;
	VtxElem[2].Usage = 0;
	VtxElem[2].UsageIndex = 0;

	this->pDevice->CreateVertexDeclaration(VtxElem, &this->pVtxDecl);
	this->pDevice->SetVertexDeclaration(this->pVtxDecl);
}

void DirectX::MessageLoop(void)
{
	this->pEffect->End();
	this->pDevice->EndScene();
	this->pDevice->Present(NULL, NULL, NULL, NULL);
	while (PeekMessage(&Window::Instance()->msg, NULL, 0U, 0U, PM_REMOVE)) {
		TranslateMessage(&Window::Instance()->msg);
		DispatchMessage(&Window::Instance()->msg);
	}
	this->pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(63, 127, 255), 1.f, 0);
	this->pDevice->BeginScene();
	this->pEffect->SetTechnique("Tech");
	this->pEffect->Begin(NULL, 0);
}

void DirectX::CalcFPS(void)
{

}

bool DirectX::Update(void)
{
	if (Window::Instance()->msg.message != WM_QUIT)
	{
		this->MessageLoop();
		this->CalcFPS();
		return true;
	}
	return false;
}

void DirectX::Uninit(void)
{
	SAFE_RELEASE(DirectX::pVtxBuf);
	SAFE_RELEASE(DirectX::pVtxDecl);
	SAFE_RELEASE(DirectX::pDevice);
	SAFE_RELEASE(DirectX::pEffect);
}