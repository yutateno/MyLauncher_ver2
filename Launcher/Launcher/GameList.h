#pragma once
#include "FolderName.h"
#include "FolderInGame.h"
#include "FolderInMedia.h"
#include "input.h"

class GameList
{
private:
	FolderName * folder_name;		// FolderName�̎���(�Q�[������������t�H���_�̖��O������)
	FolderInGame * folder_game;		// FolderInGame�̎���(�t�H���_�̃Q�[���̋N���Ɋւ���)
	FolderInMedia * folder_media;	// FolderInMedia�̎���(�t�H���_�̃Q�[���̃��f�B�A�Ɋւ���)

	int s_bgm;				// �O�����悤�ɗ���BGM(�g��Ȃ�����)

	int gamenum;			// �Q�[�������L�����

	int now_checkgame;		// �����Ă���Q�[��

	int gameReadyWait;		// �����R�}���h������������

	int fontData;			// �쐬����t�H���g�f�[�^

	bool gameReady;			// �Q�[���N���̊m�F

	bool gameReadyCheck;	// �Q�[���N���̑I��

	bool createGameFlag;	// �Q�[�����N�����Ă��邩

	bool launcher_end;		// �����`���[���I��������

	int moviecount;			// ���̓���ֈڂ�J�E���g

	void KeyAtach(int right, int left, int dicision);

public:
	GameList();		// �R���X�g���N�^
	~GameList();	// �f�X�g���N�^

	void Draw();		// �`��
	void Process();		// ���C��
	void KeyProcess();	// ����

	// �Q�b�^�[
	bool GetCreateGame();		// �Q�[���̋N��
	bool GetLauncherEnd();		// �����`���[�̏I��
};