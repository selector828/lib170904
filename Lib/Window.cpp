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
	// コンソールを作成する
	AllocConsole();
	// 標準入出力に割り当てる
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
	//ウィンドウの大きさ計算
	RECT WindowRect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, false);
	int newWidth = (SHORT)(WindowRect.right - WindowRect.left);
	int newHeight = (SHORT)(WindowRect.bottom - WindowRect.top);

	//真ん中配置時の座標計算
	RECT DeskRect;
	GetWindowRect(GetDesktopWindow(), &DeskRect);
	int newPosX = (DeskRect.right - newWidth) / 2;
	int newPosY = (DeskRect.bottom - newHeight) / 2;

	//ウィンドウ生成
	this->hWnd = CreateWindowEx(0, "SceneWndClass", GAME_TITLE, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		newPosX, newPosY, newWidth, newHeight, NULL, NULL, this->hInstance, NULL);

	//ウィンドウ更新
	UpdateWindow(this->hWnd);
	ShowWindow(this->hWnd, SW_SHOW);

	createConsoleWindow();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:Window::WmCreate(hWnd); break;                   //ウィンドウが作られた時
	case WM_COMMAND:Window::WmCommand(hWnd, wParam, lParam); break; //コマンドが送られてきた時
	case WM_PAINT:Window::WmPaint(hWnd); break;                     //ウィンドウが再描画された時
	case WM_MOVE:Window::WmMove(hWnd, lParam); break;               //ウィンドウ座標が変わった時
	case WM_SIZE:Window::WmSize(hWnd, lParam); break;               //ウィンドウ座標が変わった時
	case WM_MOUSEMOVE:Window::WmMouseMove(hWnd, lParam); break;     //マウスの座標が変わった時
	case WM_LBUTTONDOWN:Window::WmLButtonDown(hWnd); break;         //左クリックした時
	case WM_RBUTTONDOWN:Window::WmRButtonDown(hWnd); break;         //右クリックした時
	case WM_LBUTTONUP:Window::WmLButtonUp(hWnd); break;             //左クリックをやめた時
	case WM_RBUTTONUP:Window::WmRButtonUp(hWnd); break;             //右クリックをやめた時
	case WM_KEYDOWN:Window::WmKeyDown(hWnd, wParam); break;         //キーが押された時
	case WM_KEYUP:Window::WmKeyUp(hWnd, wParam); break;             //キーが離された時
	case WM_CLOSE:Window::CloseWindow(); return 0;                  //[×]ボタンが押された時
	case WM_DESTROY:PostQuitMessage(0); break;						//ウィンドウを閉じた時
	default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//【自動】ウィンドウ生成時
void Window::WmCreate(HWND hWnd) {}

//【自動】ウィンドウコマンド
void Window::WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {}

//【自動】ウィンドウ描画時
void Window::WmPaint(HWND hWnd) {}

//【自動】ウィンドウ移動時
void Window::WmMove(HWND hWnd, LPARAM lParam) {}

//【自動】マウス移動時
void Window::WmMouseMove(HWND hWnd, LPARAM lParam)
{
	Input::MousePos.X = (SHORT)LOWORD(lParam);
	Input::MousePos.Y = (SHORT)HIWORD(lParam);
}

//【自動】ウィンドウサイズ変更時
void Window::WmSize(HWND hWnd, LPARAM lParam)
{

}

//【自動】左クリックしたとき
void Window::WmLButtonDown(HWND hWnd)
{
	if (!Input::Enable)
		return;
	//クリック情報更新
	Input::bLClick = true;

	SetFocus(hWnd);
}

//【自動】右クリックしたとき
void Window::WmRButtonDown(HWND hWnd)
{
	if (!Input::Enable)
		return;
	//クリック情報更新
	Input::bRClick = true;
}

//【自動】左クリックをやめたとき
void Window::WmLButtonUp(HWND hWnd)
{
	//クリック情報更新
	Input::bLClick = false;
}

//【自動】右クリックをやめたとき
void Window::WmRButtonUp(HWND hWnd)
{
	//クリック情報更新
	Input::bRClick = false;
}

//【自動】キーが押されたとき
void Window::WmKeyDown(HWND hWnd, WPARAM wParam)
{
	if (!Input::Enable)
		return;
	//キー入力情報更新
	Input::bKeys[wParam] = true;
	//【必須】終了処理
	if (wParam == VK_ESCAPE)
		Window::CloseWindow();
}

//【自動】キーが離されたとき
void Window::WmKeyUp(HWND hWnd, WPARAM wParam)
{
	//キー入力情報更新
	Input::bKeys[wParam] = false;
}

//【呼出】ウィンドウを閉じる
void Window::CloseWindow(void)
{
	UINT uID = MessageBox(NULL, "しゅうりょうしますか。", "しゅうりょうめっせーじ", MB_YESNO | MB_DEFBUTTON2);
	if (uID == IDYES) DestroyWindow(Window::Instance()->hWnd);
}