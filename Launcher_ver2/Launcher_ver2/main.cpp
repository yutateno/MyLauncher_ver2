#include "GameList.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif

	int default_xSize;		// �f�t�H���g�E�B���h�E��X�T�C�Y
	int default_ySize;		// �f�t�H���g�E�B���h�E��Y�T�C�Y
	int bitcolor;			// �f�t�H���g�E�B���h�E�̃r�b�g�J���[�l

	bool endFlag = false;				// �G���h�R�}���h����͂��ꂽ���ǂ���
	bool endComfirm = false;			// �G���h�̊m�F

	int fontSize = 16;			// �t�H���g�T�C�Y

	int colorSelect = GetColor(0, 0, 0);		// ��

	SetWindowText("My_Launcher");	// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����

	GetDefaultState(&default_xSize, &default_ySize, &bitcolor);		// �E�B���h�E�f�t�H���g�l�𓾂�

	ChangeWindowMode(TRUE);			// �E�B���h�E�Y���[�h�ɂ����邩�ǂ���

	SetGraphMode(projectbase::WINDOW_X, projectbase::WINDOW_Y, bitcolor);					// �摜�ɍ��킹�ĉ�ʃT�C�Y��ύX
	SetWindowSize(default_xSize, default_ySize);		// �E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX

	SetBackgroundColor(220, 220, 220);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetAlwaysRunFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��

	SetFontSize(fontSize);				// �t�H���g�T�C�Y

	SetMouseDispFlag(TRUE);			// �}�E�X��\��

	GameList* game_list = new GameList(default_xSize, default_ySize);		// �����`���[�̃��C��

	// ����
	KeyData::UpDate();
	PadData::UpDate();
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 0, 0, 0, 0, 0, 0);
	MouseData::Mouse_UpDate();
	MouseWheelData::MouseWheel_Update();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !game_list->GetLauncherEnd())
	{
		// �I���R�}���h����͂��ăt���b�O�𗧂�����
		if (!KeyData::CheckEnd())	// �I���̓L�[�{�[�h�̂�
		{
			endFlag = true;
		}

		// �I���t���b�O�������Ă��Ȃ��Ƃ�
		if (!endFlag)
		{
			game_list->Draw();		// �����̂ݕ`��

			game_list->Process();		// �����`���[���̓���

			// �Q�[�����N�����Ă��Ȃ��Ƃ�
			if (!game_list->GetCreateGame())
			{
				KeyData::UpDate();
				PadData::UpDate();
				MouseData::Mouse_UpDate();
				MouseWheelData::MouseWheel_Update();
				game_list->KeyProcess();
			}
		}
		else
		{
			KeyData::UpDate();
			PadData::UpDate();
			DrawFormatString(860, 520, GetColor(255, 255, 255), "Shut Down�H\nNO     YES\n		push ENTER");

			// ��̕�����NO��YES�̐؂�ւ�
			if (KeyData::Get(KEY_INPUT_LEFT) == 1)
			{
				endComfirm = false;
			}
			if (KeyData::Get(KEY_INPUT_RIGHT) == 1)
			{
				endComfirm = true;
			}

			// �I���󋵂ɉ����ĐF��ς���
			if (endComfirm)
			{
				DrawFormatString(860, 520, GetColor(255, 0, 0), "\n       YES");
			}
			else
			{
				DrawFormatString(860, 520, GetColor(255, 0, 0), "\nNO");
			}

			// �G���^�[�L�[�������đI���󋵂ɉ�����
			if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
			{
				if (endComfirm)
				{
					break;
				}
				else
				{
					endFlag = false;
				}
			}
		}
	}

	delete game_list;

	DxLib::InitGraph();
	DxLib::InitSoundMem();
	DxLib::DxLib_End();

	return 0;
}