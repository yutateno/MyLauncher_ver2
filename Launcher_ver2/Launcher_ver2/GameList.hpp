#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	/// �|�C���^�[����------------------------------------------

	// FolderName�̎���(�Q�[������������t�H���_�̖��O������)
	FolderName* p_folder_name;		

	// FolderInGame�̎���(�t�H���_�̃Q�[���̋N���Ɋւ���)
	FolderInGame* p_folder_game;	

	// FolderInMedia�̎���(�t�H���_�̃Q�[���̃��f�B�A�Ɋւ���)
	FolderInMedia* p_folder_media;	


	// �ς����E�B���h�E�̃T�C�Y
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


	/// �摜��ۑ�����ϐ�--------------------------

	// �E�B���h�E�T�C�Y�Ɋւ���摜
	int drawWindow[10];			

	// �E�B���h�E�T�C�Y�̌���Ɋւ���摜
	int drawSelectWin;			

	// �Q�[���N���Ɋւ���摜
	int drawGameReady[4];		

	// �����`���[�̏I���Ɋւ���摜
	int drawLauncherEnd[4];		


	/// �Q�[���ꗗ�Ɋւ���-----------------

	// �V�ׂ�Q�[���̐�
	int gameNum;			

	// �����Ă���Q�[��
	int now_checkGame;		

	// ���I�����Ă���Q�[���̗�
	int selectSideNum;		
	
	
	/// �Q�[���̋N���Ɋւ���------------

	// �Q�[���N���̊m�F
	bool gameReady;			

	// �Q�[���N���̑I��
	bool gameReadyCheck;	

	// �Q�[�����N�����Ă��邩
	bool createGameFlag;	


	/// �����`���[�I���Ɋւ���------------------------------------------------

	// �����`���[���I��������
	bool launcher_end;			

	// �I���R�}���h����͂��ꂽ���ǂ���
	bool endFlag;				

	// �I���m�F��ʂł̏I���m�F
	bool endComfirm;			

	// �����`���[�I���R�}���h���I�v�V�����R�}���h�ɃJ�[�\���𓖂ĂĂ��邩
	bool endCommandForcus;		

	// �����I�������邩�ǂ���
	bool forceEnd;			

	// �����I���̊m�F��ʂ̕\������
	int forceEndCount;		


	/// �E�B���h�E�T�C�Y�ύX�Ɋւ���------------------------

	// ���Ȃ��̃f�B�X�v���C�W���E�B���h�E��X�T�C�Y
	int default_xSize;			

	// ���Ȃ��̃f�B�X�v���C�W���E�B���h�E��Y�T�C�Y
	int default_ySize;			

	// ���̎w��T�C�Y
	int numSize;				

	// �T�C�Y�ύX���X�T�C�Y
	int xSize;					

	// �T�C�Y�ύX���Y�T�C�Y
	int ySize;					

	// �Q�[����I�����Ă���(��̃I�v�V�����ł͂Ȃ�)
	bool gameSelect;			

	// �E�B���h�E�T�C�Y�ύX���j���[�̕\���t���b�O
	bool windowSizeMenuFlag;	

	// �E�B���h�E�T�C�Y��for���[�v���l�̂��߂̂���
	int optionTextFor;			

	// �E�B���h�E�T�C�Y�I�v�V�����̉��o�p�ϐ�
	int optionPerformerCount;
	/// --------------------------------------------------	


	/// ����Ɋւ���-------------------------------------------------------

	// �_�u���N���b�N�������Ȃ�(�����̃f�o�C�X���瓯���Ɏ擾���Ă��邽��)
	int doubleSelectWait;		

	

	/// �`��̃v���Z�X------------------------

	// �Q�[���N���Ɋւ���`��
	void DrawGameFileScroll();		

	// �I�v�V�����Ɋւ���`��
	void DrawOption();				


	/// ����̃v���Z�X---------------------------------------------------------------

	// ����
	void KeyProcess();																	

	// �I�v�V�����̑���Ɋւ���
	void OptionKeyProcess(int right, int left, int up, int down, int dicision);			

	// �Q�[���N���̑���Ɋւ���
	void GameUpdate(int right, int left, int dicision);								

	// �����`���[�I���̑���Ɋւ���
	void LauncherEnd(int left, int right, int dicision);


public:
	GameList(int defaultXSize, int defaultYSize);		// �R���X�g���N�^
	~GameList();										// �f�X�g���N�^


	void Draw();		// �`��
	void Process();		// ���C��


	// �Q�b�^�[
	bool GetCreateGame();		// �Q�[���̋N��
	bool GetLauncherEnd();		// �����`���[�̏I��
};