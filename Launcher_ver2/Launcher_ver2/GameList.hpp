#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	// �|�C���^�[����
	FolderName* p_folder_name;		// FolderName�̎���(�Q�[������������t�H���_�̖��O������)
	FolderInGame* p_folder_game;		// FolderInGame�̎���(�t�H���_�̃Q�[���̋N���Ɋւ���)
	FolderInMedia* p_folder_media;	// FolderInMedia�̎���(�t�H���_�̃Q�[���̃��f�B�A�Ɋւ���)


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


	// �摜��ۑ�����ϐ�
	int drawWindow[10];			// �E�B���h�E�T�C�Y�Ɋւ���摜
	int drawSelectWin;			// �E�B���h�E�T�C�Y�̌���Ɋւ���摜
	int drawGameReady[4];		// �Q�[���N���Ɋւ���摜
	int drawLauncherEnd[4];		// �����`���[�̏I���Ɋւ���摜


	// �Q�[���ꗗ�Ɋւ���
	int gameNum;			// �V�ׂ�Q�[���̐�
	int now_checkGame;		// �����Ă���Q�[��
	int selectSideNum;		// ���I�����Ă���Q�[���̗�
	
	
	// �Q�[���̋N���Ɋւ���
	bool gameReady;			// �Q�[���N���̊m�F
	bool gameReadyCheck;	// �Q�[���N���̑I��
	bool createGameFlag;	// �Q�[�����N�����Ă��邩


	// �����`���[�I���Ɋւ���
	bool launcher_end;			// �����`���[���I��������
	bool endFlag;				// �I���R�}���h����͂��ꂽ���ǂ���
	bool endComfirm;			// �I���m�F��ʂł̏I���m�F
	bool endCommandForcus;		// �����`���[�I���R�}���h���I�v�V�����R�}���h�ɃJ�[�\���𓖂ĂĂ��邩
	bool forceEnd;				// �����I�������邩�ǂ���


	// �E�B���h�E�T�C�Y�ύX�Ɋւ���
	int default_xSize;			// ���Ȃ��̃f�B�X�v���C�W���E�B���h�E��X�T�C�Y
	int default_ySize;			// ���Ȃ��̃f�B�X�v���C�W���E�B���h�E��Y�T�C�Y
	int numSize;				// ���̎w��T�C�Y
	int xSize;					// �T�C�Y�ύX���X�T�C�Y
	int ySize;					// �T�C�Y�ύX���Y�T�C�Y
	bool gameSelect;			// �Q�[����I�����Ă���(��̃I�v�V�����ł͂Ȃ�)
	bool windowSizeMenuFlag;	// �E�B���h�E�T�C�Y�ύX���j���[�̕\���t���b�O
	int optionTextFor;			// �E�B���h�E�T�C�Y��for���[�v���l�̂��߂̂���

	

	// �`��̃v���Z�X
	void DrawGameFileScroll();		// �Q�[���N���Ɋւ���`��
	void DrawOption();				// �I�v�V�����Ɋւ���`��


	// ����̃v���Z�X
	void KeyProcess();																	// ����
	void OptionKeyProcess(int right, int left, int up, int down, int dicision);			// �I�v�V�����̑���Ɋւ���
	void GameUpdate(int right, int left, int dicision);									// �Q�[���N���̑���Ɋւ���
	void LauncherEnd(int left, int right, int dicision);								// �����`���[�I���̑���Ɋւ���

public:
	GameList(int defaultXSize, int defaultYSize);		// �R���X�g���N�^
	~GameList();	// �f�X�g���N�^


	void Draw();		// �`��
	void Process();		// ���C��


	// �Q�b�^�[
	bool GetCreateGame();		// �Q�[���̋N��
	bool GetLauncherEnd();		// �����`���[�̏I��
};