//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �d���C���N���[�h�h�~
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#pragma once
#include "DirectX.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �}�N����`
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#define KEY_MAX (256)
#define XINPUT_MAX (0xffff)

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �N���X
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class Input
{
public:
	static bool  Enable;
	static bool  bKeys[KEY_MAX];
	static UINT  uKeys[KEY_MAX];
	static bool  bLClick;
	static bool  bRClick;
	static UINT  uLClick;
	static UINT  uRClick;
	static COORD MousePos;
	static XINPUT_STATE XInputState;
	static bool  bController[XINPUT_MAX];
	static UINT	 uController[XINPUT_MAX];
	static void  Update(void);
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// End.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+