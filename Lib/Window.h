//重複インクルード防止
#pragma once

//インクルードファイル
#include <windows.h> //Windowsライブラリ
#include "Input.h"

//警告
#pragma warning(disable: 4100)
#pragma warning(disable: 4238)
#pragma warning(disable: 4458)
#pragma warning(disable: 4474)
#pragma warning(disable: 4476)
#pragma warning(disable: 4996)

//ゲームタイトル
#define GAME_TITLE "ゲームタイトル"

//マクロ定義
#define SCREEN_WIDTH  (1280) //スクリーンサイズ(横)
#define SCREEN_HEIGHT ( 720) //スクリーンサイズ(縦)
#define SCREEN_CENTER D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)

// "安全な"COMポインタの解放処理マクロ
#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL; }
// "安全な"配列の解放処理マクロ
#define SAFE_DELETE(p) if(p){ delete[] p; p = NULL; }

//WinMainの引数
#define WIN_PARAM HINSTANCE, HINSTANCE, LPSTR, int

class Window final
{
public:
	HWND                         hWnd;
	MSG                          msg;
	HINSTANCE                    hInstance;

public:
	static Window * Instance(void)
	{
		static Window $this = {};

		return &$this;
	};

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	void Setup(void);
	void Create(void);
public:
	static void WmCreate(HWND hWnd);
	static void WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void WmPaint(HWND hWnd);
	static void WmMove(HWND hWnd, LPARAM lParam);
	static void WmMouseMove(HWND hWnd, LPARAM lParam);
	static void WmSize(HWND hWnd, LPARAM lParam);
	static void WmLButtonDown(HWND hWnd);
	static void WmRButtonDown(HWND hWnd);
	static void WmLButtonUp(HWND hWnd);
	static void WmRButtonUp(HWND hWnd);
	static void WmKeyDown(HWND hWnd, WPARAM wParam);
	static void WmKeyUp(HWND hWnd, WPARAM wParam);
	static void CloseWindow(void);
private:
	Window(void);

};