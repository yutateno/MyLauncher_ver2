#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	FolderName* p_folder_name;		// FolderName�̎���(�Q�[������������t�H���_�̖��O������)
	FolderInGame* p_folder_game;		// FolderInGame�̎���(�t�H���_�̃Q�[���̋N���Ɋւ���)
	FolderInMedia* p_folder_media;	// FolderInMedia�̎���(�t�H���_�̃Q�[���̃��f�B�A�Ɋւ���)

	int gamenum;			// �Q�[�������L�����

	int now_checkgame;		// �����Ă���Q�[��

	int gameReadyWait;		// �����R�}���h������������

	int fontData;			// �쐬����t�H���g�f�[�^

	bool gameReady;			// �Q�[���N���̊m�F

	bool gameReadyCheck;	// �Q�[���N���̑I��

	bool createGameFlag;	// �Q�[�����N�����Ă��邩

	bool launcher_end;		// �����`���[���I��������

	void GameUpdate(int right, int left, int dicision);


	// �ς����E�B���h�E�̃T�C�Y(X��Y�������z�~��������)(�{����enum�̐��l��X���W�����for�񂵂����������Ǐo���Ȃ�����Ë�)
	struct SizeWindow {
		enum Select
		{
			Default,		// �ꉞ�A���ɈӖ��͂Ȃ�
			First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth,
		};
		Select type;

		SizeWindow(Select v) : type(v) {}
		operator enum Select() { return type; }

		static int SelectX(int x)
		{
			switch (x)
			{
			case First:		return 640;
			case Second:	return 768;
			case Third:		return 1024;
			case Fourth:	return 1280;
			case Fifth:		return 1366;
			case Sixth:		return 1920;
			case Seventh:	return 2048;
			case Eighth:	return 2560;
			case Ninth:		return 3200;
			default:		return 1;		// �ꉞ�A���ɈӖ��͂Ȃ�
			}
		}

		static int SelectY(int y)
		{
			switch (y)
			{
			case First:		return 480;
			case Second:	return 576;
			case Third:		return 768;
			case Fourth:	return 720;
			case Fifth:		return 768;
			case Sixth:		return 1080;
			case Seventh:	return 1536;
			case Eighth:	return 1440;
			case Ninth:		return 2400;
			default:		return 1;		// �ꉞ�A���ɈӖ��͂Ȃ�
			}
		}
	};

	int default_xSize;		// �f�t�H���g�E�B���h�E��X�T�C�Y
	int default_ySize;		// �f�t�H���g�E�B���h�E��Y�T�C�Y

	int numSize;
	int xSize;			// �T�C�Y�ύX���X�T�C�Y
	int ySize;			// �T�C�Y�ύX���Y�T�C�Y

	bool gameSelect;


	int drawWindow[10];

	int drawSelectWin;

	bool windowSizeMenuFlag;	// �E�B���h�E�T�C�Y�ύX���j���[�̕\���t���b�O


	int optionTextFor;		// for���[�v���l�̂��߂̂���

	int drawGameReady[4];


	int optionPerformerCount;


	void DrawGameFileScroll();


	void DrawOption();


	int scrollNum;

	int selectSideNum;


	bool endFlag;				// �G���h�R�}���h����͂��ꂽ���ǂ���


	bool endComfirm;			// �G���h�̊m�F


	void LauncherEnd();


	void KeyProcess();	// ����


	int drawLauncherEnd[4];

	bool endOrOption;

public:
	GameList(int defaultXSize, int defaultYSize);		// �R���X�g���N�^
	~GameList();	// �f�X�g���N�^


	void Draw();		// �`��
	void Process();		// ���C��


	// �Q�b�^�[
	bool GetCreateGame();		// �Q�[���̋N��
	bool GetLauncherEnd();		// �����`���[�̏I��
	bool GetEndFlag();
};