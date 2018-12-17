#include "GameList.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif

	int default_xSize = 1920;		// �f�t�H���g�E�B���h�E��X�T�C�Y
	int default_ySize = 1080;		// �f�t�H���g�E�B���h�E��Y�T�C�Y
	int bitcolor = 32;				// �f�t�H���g�E�B���h�E�̃r�b�g�J���[�l


	int fontSize = 48;			// �t�H���g�T�C�Y


	SetWindowText("My_Launcher");	// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����


	GetDefaultState(&default_xSize, &default_ySize, &bitcolor);		// �E�B���h�E�f�t�H���g�l�𓾂�


	ChangeWindowMode(TRUE);			// �E�B���h�E�Y���[�h�ɂ����邩�ǂ���


	SetGraphMode(1920, 1080, bitcolor);					// �摜�ɍ��킹�ĉ�ʃT�C�Y��ύX
	SetWindowSize(default_xSize, default_ySize);		// �E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	SetBackgroundColor(230, 230, 230);			// �w�i�F


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}


	SetAlwaysRunFlag(TRUE);					// ����ʂł�����


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��


	SetFontSize(fontSize);				// �t�H���g�T�C�Y


	SetMouseDispFlag(TRUE);			// �}�E�X��\��


	GameList* game_list = NULL;
	game_list = new GameList(default_xSize, default_ySize);		// �����`���[�̃��C��


	// ����
	KeyData::UpDate();
	PadData::UpDate();
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 0, 0, 0, 0, 0, 0);
	MouseData::Mouse_UpDate();
	MouseWheelData::MouseWheel_Update();


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !game_list->GetLauncherEnd())
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
		}
	}


	POINTER_RELEASE(game_list);


	InitGraph();
	InitSoundMem();
	DxLib_End();


	return 0;
}