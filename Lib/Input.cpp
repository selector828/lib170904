//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// input.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "Input.h" //コアヘッダー

template<class T>
inline bool bitcheck(const T& num, int checkbit)
{
	return ((num >> checkbit) & 1);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 静的変数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool Input::Enable = true;
bool Input::bKeys[KEY_MAX] = {};
UINT Input::uKeys[KEY_MAX] = {};
bool Input::bLClick = false;
bool Input::bRClick = false;
UINT  Input::uLClick = 0;
UINT  Input::uRClick = 0;
COORD Input::MousePos = {};
XINPUT_STATE Input::XInputState = {};
bool	Input::bController[XINPUT_MAX] = {};
UINT	Input::uController[XINPUT_MAX] = {};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 静的関数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Input::Update(void)
{
	XInputGetState(0, &Input::XInputState);

	if (Input::Enable)
		Input::bController[Input::XInputState.Gamepad.wButtons] = true;

	for (UINT u = 0; u < KEY_MAX; u++)
	{
		if (Input::bKeys[u])
		{
			Input::uKeys[u]++;
		}
		else
		{
			Input::uKeys[u] = 0;
		}
	}

	//for (UINT u = 0; u < XINPUT_MAX; u++)
	//{
	//	if (Input::bController[u])
	//	{
	//		Input::uController[u]++;
	//	}
	//	else
	//	{
	//		Input::uController[u] = 0;
	//	}
	//}

	for (int n = 1; n <= 16; n++)
	{
		if (bitcheck<WORD>(Input::XInputState.Gamepad.wButtons, n))
		{
			Input::uController[Input::XInputState.Gamepad.wButtons]++;
		}
		else
		{
			Input::uController[Input::XInputState.Gamepad.wButtons] = 0;
		}
	}


	if (Input::bLClick)
	{
		Input::uLClick++;
	}
	else
	{
		Input::uLClick = 0;
	}

	if (Input::bRClick)
	{
		Input::uRClick++;
	}
	else
	{
		Input::uRClick = 0;
	}

	Input::bController[Input::XInputState.Gamepad.wButtons] = false;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// End.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+