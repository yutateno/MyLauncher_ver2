#pragma once
#include "ProjectBase.hpp"

#include <vector>

#pragma warning(disable : 4996)

class FolderName
{
private:
	char Path[MAX_PATH + 1];	// ���s�t�@�C���̊��S�p�X���擾����ϐ�

	char drive[MAX_PATH + 1]	// �h���C�u
		, dir[MAX_PATH + 1]		// �f�B���N�g���p�X
		, fname[MAX_PATH + 1]	// �t�@�C����
		, ext[MAX_PATH + 1];	// �t�@�C�����̊g���q

	int gamenum;		// �J�����g�f�B���N�g���ɓ���Ă���Q�[���̐�

	std::string gamePath;	// �����`���[.exe�̃p�X

	std::string tempPath;	// createPath�֓n�����߂̉��u���̃p�X�ێ��ϐ�

	std::string createPath;	// �Q�[�����N�����邽�߂̃p�X


	// �z�񐔂����Q�[���̐�������A�X�ŃQ�[����Launcher�t�H���_�ɓ����Ă邻�ꂼ��̖��O�𓾂���
	std::vector<std::string> foldername;			// �Q�[���̖��O
	std::vector<std::string> moviename;			// ����̖��O
	std::vector<std::string> drawname;			// �摜�̖��O
	std::vector<std::string> textname;			// �e�L�X�g�̖��O


	std::string SearchMediaFile(std::string gamePath, std::string gamefilename, std::string extension);				// �����`���[�̂��߂̃Q�[���̃��f�B�A�ނ̖��O�����ꂼ�꒲�ׂ�
	void SearchDrawFile(std::string gamePath, std::string gamefilename, std::string extension);	// �摜�p��(�����`���[�̂��߂̃Q�[���̃��f�B�A�ނ̖��O�����ꂼ�꒲�ׂ�)
	void SearchGameFile(std::string gamePath);													// �����`���[.exe�Ɠ����K�w�ɓ��ꂽ�Q�[���̃t�H���_���𒲂ׂ�
	HANDLE hFind;																				// �t�H���_���m�F����
	int fileCount;																				// �t�H���_�̐��𓾂�
	WIN32_FIND_DATA FindFileData;																// �m�F�����t�H���_�̖��O�𓾂�


public:
	FolderName();		// �R���X�g���N�^
	~FolderName();		// �f�X�g���N�^


	// �Q�b�^�[
	int GetGameNum();							// �Q�[���̌�
	std::string GetPathName();						// �Q�[���̃p�X
	std::string GetFolderName(int catch_number);		// �Q�[���̃t�H���_��
	std::vector<std::string> GetGameListName();			// �Q�[���̖��O�Q
	std::vector<std::string> GetMovieListName();			// �Q�[���̓���Q
	std::vector<std::string> GetDrawListName();	// �Q�[���̉摜�Q
	std::vector<std::string> GetTextListName();			// �Q�[���̃e�L�X�g�Q
};