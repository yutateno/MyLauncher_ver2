#include "Input.hpp"

namespace ps = padstick;

//////////////////////////////////////////////�L�[�{�[�h////////////////////////////////////////////////////
KeyData::KeyData()
{

}

KeyData::~KeyData()
{

}

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate()
{
	KeyData::tmpKey[256];			// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(KeyData::tmpKey);	// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++)
	{
		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;   // ���Z
		}
		// �L�[�������ꂽ�u��
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1; // -1�ɂ���
		}
		// ����ȊO
		else
		{
			KeyData::key[i] = 0; // 0�ɂ���
		}
	}
}

bool KeyData::CheckEnd()
{
	return { KeyData::key[KEY_INPUT_ESCAPE] <= 0 };
}

int KeyData::Get(int KeyCode)
{
	return KeyData::key[KeyCode];
}

//////////////////////////////////////////////�Q�[���p�b�h////////////////////////////////////////////////////


PadData::PadData()
{

}

PadData::~PadData()
{

}

int PadData::button[4][16];  // �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
int PadData::stick[4][6];
int PadData::stickCheck[4][8];
short PadData::thumbLX_DeadMAX;
short PadData::thumbLX_DeadMIN;
short PadData::thumbLY_DeadMAX;
short PadData::thumbLY_DeadMIN;
short PadData::thumbRX_DeadMAX;
short PadData::thumbRX_DeadMIN;
short PadData::thumbRY_DeadMAX;
short PadData::thumbRY_DeadMIN;
XINPUT_STATE PadData::input[4];	// �Q�[���p�b�h�̃i���o�[
__int8 PadData::padNum;

void PadData::SetPadNum()
{
	PadData::padNum = (__int8)GetJoypadNum();
}

void PadData::SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
	, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN)
{
	PadData::thumbLX_DeadMAX = thumbLX_MAX;
	PadData::thumbLX_DeadMIN = thumbLX_MIN;
	PadData::thumbLY_DeadMAX = thumbLY_MAX;
	PadData::thumbLY_DeadMIN = thumbLY_MIN;
	PadData::thumbRX_DeadMAX = thumbRX_MAX;
	PadData::thumbRX_DeadMIN = thumbRX_MIN;
	PadData::thumbRY_DeadMAX = thumbRY_MAX;
	PadData::thumbRY_DeadMIN = thumbRY_MIN;
}

void PadData::UpDate()
{
	for (int j = 0; j < PadData::padNum; j++)
	{
		// ���͏�Ԃ��擾
		switch (j)
		{
		case 0:
			GetJoypadXInputState(DX_INPUT_PAD1, &PadData::input[j]);
			break;
		case 1:
			GetJoypadXInputState(DX_INPUT_PAD2, &PadData::input[j]);
			break;
		case 2:
			GetJoypadXInputState(DX_INPUT_PAD3, &PadData::input[j]);
			break;
		case 3:
			GetJoypadXInputState(DX_INPUT_PAD4, &PadData::input[j]);
			break;
		default:
			break;
		}
		for (int i = 0; i < 16; i++)
		{
			// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			if (PadData::input[j].Buttons[i] != 0)
			{
				PadData::button[j][i]++;   // ���Z
			}
			// �L�[�������ꂽ�u��
			else if (PadData::button[j][i] > 0)  // ����Ń_���������猳�́ubutton[i] > 0�v�ɖ߂��āB�ł����ꂨ�������Ǝv��
			{
				PadData::button[j][i] = -1; // -1�ɂ���
			}
			// ����ȊO
			else
			{
				PadData::button[j][i] = 0; // 0�ɂ���
			}
		}

		// �g���K�[�̓��͐��l���擾
		PadData::stick[j][ps::XINPUT_LEFT_TRIGGER] = PadData::input[j].LeftTrigger;
		PadData::stick[j][ps::XINPUT_RIGHT_TRIGGER] = PadData::input[j].RightTrigger;

		// �X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾
		if (PadData::input[j].ThumbLX > PadData::thumbLX_DeadMAX || PadData::input[j].ThumbLX < PadData::thumbLX_DeadMIN)
		{
			PadData::stick[j][ps::XINPUT_LEFT_THUMB_X] = PadData::input[j].ThumbLX;
		}
		if (PadData::input[j].ThumbLY > PadData::thumbLY_DeadMAX || PadData::input[j].ThumbLY < PadData::thumbLY_DeadMIN)
		{
			PadData::stick[j][ps::XINPUT_LEFT_THUMB_Y] = PadData::input[j].ThumbLY;
		}
		if (PadData::input[j].ThumbRX > PadData::thumbRX_DeadMAX || PadData::input[j].ThumbRX < PadData::thumbRX_DeadMIN)
		{
			PadData::stick[j][ps::XINPUT_RIGHT_THUMB_X] = PadData::input[j].ThumbRX;
		}
		if (PadData::input[j].ThumbRY > PadData::thumbRY_DeadMAX || PadData::input[j].ThumbRY < PadData::thumbRY_DeadMIN)
		{
			PadData::stick[j][ps::XINPUT_RIGHT_THUMB_Y] = PadData::input[j].ThumbRY;
		}

		// �X�e�B�b�N�̉����|�����͂��擾
		if (PadData::input[j].ThumbLX == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (PadData::input[j].ThumbLX == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (PadData::input[j].ThumbLY == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (PadData::input[j].ThumbLY == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[j][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (PadData::input[j].ThumbRX == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (PadData::input[j].ThumbRX == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (PadData::input[j].ThumbRY == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (PadData::input[j].ThumbRY == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[j][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
	}
}

// �Q�[���p�b�h�̓��͏�Ԏ擾
int PadData::Get(int code, int padNum)
{
	return PadData::button[padNum][code];
}

int PadData::GetStick(int code, int padNum)
{
	return PadData::stick[padNum][code];
}

int PadData::GetStickCheck(int code, int padNum, bool plus)
{
	if (plus)
	{
		return PadData::stickCheck[padNum][code - 2];
	}
	else
	{
		return PadData::stickCheck[padNum][code - 2 - 4];
	}
}

__int8 PadData::GetPadNum()
{
	return PadData::padNum;
}

bool PadData::CheckEnd()
{
	return
	{
		(PadData::button[0][XINPUT_BUTTON_START] < 1 && PadData::button[0][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[1][XINPUT_BUTTON_START] < 1 && PadData::button[1][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[2][XINPUT_BUTTON_START] < 1 && PadData::button[2][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[3][XINPUT_BUTTON_START] < 1 && PadData::button[3][XINPUT_BUTTON_BACK] < 1)
	};
}


//////////////////////////////////////////////�}�E�X�֘A////////////////////////////////////////////////////

MouseData::MouseData()
{

}

MouseData::~MouseData()
{

}

int MouseData::m_Mouse[3];
int MouseData::MouseInput;

void MouseData::Mouse_UpDate() {
	MouseInput = GetMouseInput();    //�}�E�X�̉�������Ԏ擾
	for (int i = 0; i < 3; i++) {
		if ((MouseInput & 1 << i) != 0) {
			m_Mouse[i]++;   //������Ă�����J�E���g�A�b�v
		}
		else {
			m_Mouse[i] = 0; //������ĂȂ�������0
		}
	}
}

int MouseData::GetClick(int MouseCode) {
	return m_Mouse[MouseCode];
}

//////////////////////////////////////////////�}�E�X�z�C�[���֘A////////////////////////////////////////////////////
MouseWheelData::MouseWheelData()
{

}

MouseWheelData::~MouseWheelData()
{

}

int MouseWheelData::m_MouseWheel;
int MouseWheelData::old_MouseWheel;

void MouseWheelData::MouseWheel_Update() {
	old_MouseWheel = m_MouseWheel;
	if (old_MouseWheel - m_MouseWheel > 0) {
		m_MouseWheel++;
	}
	else if (old_MouseWheel - m_MouseWheel < 0) {
		m_MouseWheel--;
	}
	else {
		m_MouseWheel = 0;
	}
}

int MouseWheelData::GetMouseWheel(int MouseWheelCode) {
	return m_MouseWheel += MouseWheelCode;
}