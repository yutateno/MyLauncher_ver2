#pragma once
#include "DxLib.h"

// input.h
#ifndef _INPUT_H
#define _INPUT_H
namespace padstick
{
	const int XINPUT_LEFT_TRIGGER = 0;
	const int XINPUT_RIGHT_TRIGGER = 1;
	const int  XINPUT_LEFT_THUMB_X = 2;
	const int  XINPUT_LEFT_THUMB_Y = 3;
	const int  XINPUT_RIGHT_THUMB_X = 4;
	const int  XINPUT_RIGHT_THUMB_Y = 5;

	const int  XINPUT_THUMB_MAX = 32767;
	const int  XINPUT_THUMB_MIN = -32768;

	const int XINPUT_THUMB_PLUS = 0;
	const int XINPUT_THUMB_MINUS = 4;
}
#endif // !_INPUT_H

// �L�[�{�[�h�̓��͏��
class KeyData
{
private:
	static int key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	static char tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����

public:
	KeyData();
	~KeyData();

	static void UpDate();			// �L�[���͂̏�ԍX�V
	static int Get(int KeyCode);	// �L�[���͏�Ԏ擾
	static bool CheckEnd();			// �����I��
};


// �Q�[���p�b�h�̓��͏��
class PadData {
	static int button[4][16];		// �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
	static int stick[4][6];			// �Q�[���p�b�h�̃X�e�B�b�N�֘A�̓��͏�Ԏ��[�p�ϐ�
	static int stickCheck[4][8];	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ��[�p�ϐ��̍ő�܂ł̓|���`�F�b�N

	// �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
	static short thumbLX_DeadMAX;
	static short thumbLX_DeadMIN;
	static short thumbLY_DeadMAX;
	static short thumbLY_DeadMIN;
	static short thumbRX_DeadMAX;
	static short thumbRX_DeadMIN;
	static short thumbRY_DeadMAX;
	static short thumbRY_DeadMIN;

	static XINPUT_STATE input[4];	// �Q�[���p�b�h�̃i���o�[
	static __int8 padNum;			// �q�����Ă�Q�[���p�b�h�̐�

public:
	PadData();
	~PadData();

	static void SetPadNum();																			// �ڑ�����Ă�Q�[���p�b�h���m�F
	static void SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
		, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN);					// �f�b�h�]�[���̐ݒ�
	static void UpDate();																				// �Q�[���p�b�h�̓��͂̏�ԍX�V
	static int Get(int code, int padNum);																// �Q�[���p�b�h�̓��͏�Ԏ擾
	static int GetStick(int code, int padNum);															// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ擾
	static int GetStickCheck(int code, int padNum, bool plus);														// �Q�[���p�b�h�̃X�e�B�b�N�̉����|�����͏�Ԏ擾
	static __int8 GetPadNum();																			// �ڑ�����Ă�Q�[���p�b�h�̐�
	static bool CheckEnd();																				// �����I��
};