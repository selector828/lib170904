#include "Window.h"

Window::Window(void)
{
	this->hWnd = NULL;
	this->msg = {};
	this->hInstance = NULL;

	this->Setup();
	this->Create();
}

void createConsoleWindow() {
	// �R���\�[�����쐬����
	AllocConsole();
	// �W�����o�͂Ɋ��蓖�Ă�
	FILE* fp = NULL;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	SetConsoleTitle("Debug Window");
}

void Window::Setup(void)
{
	ZeroMemory(&this->msg, sizeof(this->msg));
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = Window::WndProc;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hInstance = this->hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "SceneWndClass";
	wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	RegisterClassEx(&wndClass);
}

void Window::Create(void)
{
	//�E�B���h�E�̑傫���v�Z
	RECT WindowRect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, false);
	int newWidth = (SHORT)(WindowRect.right - WindowRect.left);
	int newHeight = (SHORT)(WindowRect.bottom - WindowRect.top);

	//�^�񒆔z�u���̍��W�v�Z
	RECT DeskRect;
	GetWindowRect(GetDesktopWindow(), &DeskRect);
	int newPosX = (DeskRect.right - newWidth) / 2;
	int newPosY = (DeskRect.bottom - newHeight) / 2;

	//�E�B���h�E����
	this->hWnd = CreateWindowEx(0, "SceneWndClass", GAME_TITLE, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		newPosX, newPosY, newWidth, newHeight, NULL, NULL, this->hInstance, NULL);

	//�E�B���h�E�X�V
	UpdateWindow(this->hWnd);
	ShowWindow(this->hWnd, SW_SHOW);

	createConsoleWindow();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:Window::WmCreate(hWnd); break;                   //�E�B���h�E�����ꂽ��
	case WM_COMMAND:Window::WmCommand(hWnd, wParam, lParam); break; //�R�}���h�������Ă�����
	case WM_PAINT:Window::WmPaint(hWnd); break;                     //�E�B���h�E���ĕ`�悳�ꂽ��
	case WM_MOVE:Window::WmMove(hWnd, lParam); break;               //�E�B���h�E���W���ς������
	case WM_SIZE:Window::WmSize(hWnd, lParam); break;               //�E�B���h�E���W���ς������
	case WM_MOUSEMOVE:Window::WmMouseMove(hWnd, lParam); break;     //�}�E�X�̍��W���ς������
	case WM_LBUTTONDOWN:Window::WmLButtonDown(hWnd); break;         //���N���b�N������
	case WM_RBUTTONDOWN:Window::WmRButtonDown(hWnd); break;         //�E�N���b�N������
	case WM_LBUTTONUP:Window::WmLButtonUp(hWnd); break;             //���N���b�N����߂���
	case WM_RBUTTONUP:Window::WmRButtonUp(hWnd); break;             //�E�N���b�N����߂���
	case WM_KEYDOWN:Window::WmKeyDown(hWnd, wParam); break;         //�L�[�������ꂽ��
	case WM_KEYUP:Window::WmKeyUp(hWnd, wParam); break;             //�L�[�������ꂽ��
	case WM_CLOSE:Window::CloseWindow(); return 0;                  //[�~]�{�^���������ꂽ��
	case WM_DESTROY:PostQuitMessage(0); break;						//�E�B���h�E�������
	default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//�y�����z�E�B���h�E������
void Window::WmCreate(HWND hWnd) {}

//�y�����z�E�B���h�E�R�}���h
void Window::WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {}

//�y�����z�E�B���h�E�`�掞
void Window::WmPaint(HWND hWnd) {}

//�y�����z�E�B���h�E�ړ���
void Window::WmMove(HWND hWnd, LPARAM lParam) {}

//�y�����z�}�E�X�ړ���
void Window::WmMouseMove(HWND hWnd, LPARAM lParam)
{
	Input::MousePos.X = (SHORT)LOWORD(lParam);
	Input::MousePos.Y = (SHORT)HIWORD(lParam);
}

//�y�����z�E�B���h�E�T�C�Y�ύX��
void Window::WmSize(HWND hWnd, LPARAM lParam)
{

}

//�y�����z���N���b�N�����Ƃ�
void Window::WmLButtonDown(HWND hWnd)
{
	if (!Input::Enable)
		return;
	//�N���b�N���X�V
	Input::bLClick = true;

	SetFocus(hWnd);
}

//�y�����z�E�N���b�N�����Ƃ�
void Window::WmRButtonDown(HWND hWnd)
{
	if (!Input::Enable)
		return;
	//�N���b�N���X�V
	Input::bRClick = true;
}

//�y�����z���N���b�N����߂��Ƃ�
void Window::WmLButtonUp(HWND hWnd)
{
	//�N���b�N���X�V
	Input::bLClick = false;
}

//�y�����z�E�N���b�N����߂��Ƃ�
void Window::WmRButtonUp(HWND hWnd)
{
	//�N���b�N���X�V
	Input::bRClick = false;
}

//�y�����z�L�[�������ꂽ�Ƃ�
void Window::WmKeyDown(HWND hWnd, WPARAM wParam)
{
	if (!Input::Enable)
		return;
	//�L�[���͏��X�V
	Input::bKeys[wParam] = true;
	//�y�K�{�z�I������
	if (wParam == VK_ESCAPE)
		Window::CloseWindow();
}

//�y�����z�L�[�������ꂽ�Ƃ�
void Window::WmKeyUp(HWND hWnd, WPARAM wParam)
{
	//�L�[���͏��X�V
	Input::bKeys[wParam] = false;
}

//�y�ďo�z�E�B���h�E�����
void Window::CloseWindow(void)
{
	UINT uID = MessageBox(NULL, "���イ��傤���܂����B", "���イ��傤�߂����[��", MB_YESNO | MB_DEFBUTTON2);
	if (uID == IDYES) DestroyWindow(Window::Instance()->hWnd);
}