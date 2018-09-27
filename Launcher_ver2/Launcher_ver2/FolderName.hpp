#pragma once
#include "ProjectBase.hpp"

#include <vector>

#pragma warning(disable : 4996)

class FolderName
{
private:
	// �����`���[�̃p�X�Ɋւ���
	char Path[MAX_PATH + 1];	// ���s�t�@�C���̊��S�p�X���擾����ϐ�

	char drive[MAX_PATH + 1]	// �h���C�u
		, dir[MAX_PATH + 1]		// �f�B���N�g���p�X
		, fname[MAX_PATH + 1]	// �t�@�C����
		, ext[MAX_PATH + 1];	// �t�@�C�����̊g���q
	
	std::string gamePath;		// �����`���[.exe�̃p�X


	// �Q�[���t�@�C�������Ɋւ���
	std::vector<std::string> v_folderName;		// �Q�[���̖��O
	std::vector<std::string> v_movieName;		// ����̖��O
	std::vector<std::string> v_drawName;		// �摜�̖��O
	std::vector<std::string> v_textName;		// �e�L�X�g�̖��O


	// �Q�[���t�@�C����T���Ɋւ���
	std::string SearchMediaFile(std::string gamePath, std::string gamefilename, std::string extension);				// �����`���[�̂��߂̃Q�[���̃��f�B�A�ނ̖��O�����ꂼ�꒲�ׂ�
	void SearchGameFile(std::string gamePath);																		// �����`���[.exe�Ɠ����K�w�ɓ��ꂽ�Q�[���̃t�H���_���𒲂ׂ�
	

public:
	FolderName();		// �R���X�g���N�^
	~FolderName();		// �f�X�g���N�^


	// �Q�b�^�[
	const int GetGameNum() const;									// �Q�[���̌�
	const std::string GetPathName() const;							// �Q�[���̃p�X
	const std::string GetFolderName(const int catch_number) const;	// �Q�[���̃t�H���_��
	const std::vector<std::string> GetGameListName() const;			// �Q�[���̖��O�Q
	const std::vector<std::string> GetMovieListName() const;		// �Q�[���̓���Q
	const std::vector<std::string> GetDrawListName() const;			// �Q�[���̉摜�Q
	const std::vector<std::string> GetTextListName() const;			// �Q�[���̃e�L�X�g�Q
};