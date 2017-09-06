//�d���C���N���[�h�h�~
#pragma once

//�C���N���[�h�t�@�C��
#include <windows.h> //Windows���C�u����
#include "Input.h"

//�x��
#pragma warning(disable: 4100)
#pragma warning(disable: 4238)
#pragma warning(disable: 4458)
#pragma warning(disable: 4474)
#pragma warning(disable: 4476)
#pragma warning(disable: 4996)

//�Q�[���^�C�g��
#define GAME_TITLE "�Q�[���^�C�g��"

//�}�N����`
#define SCREEN_WIDTH  (1280) //�X�N���[���T�C�Y(��)
#define SCREEN_HEIGHT ( 720) //�X�N���[���T�C�Y(�c)
#define SCREEN_CENTER D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)

// "���S��"COM�|�C���^�̉�������}�N��
#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL; }
// "���S��"�z��̉�������}�N��
#define SAFE_DELETE(p) if(p){ delete[] p; p = NULL; }

//WinMain�̈���
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