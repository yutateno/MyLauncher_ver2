#pragma once
#include "ProjectBase.h"

class FolderInGame
{
private:
	BOOL bResult;		// �v���Z�X���N���������ǂ���

	std::string gamePath;	// �Q�[���̃p�X
	std::string direPath;	// �f�B���N�g���̃p�X

public:
	FolderInGame() : bResult(FALSE) {}		// �R���X�g���N�^
	~FolderInGame() {}	// �f�X�g���N�^

	void Process(std::string createPath, std::string folderName);		// ���C��/ exe�̊K�w�܂ł̃p�X��ۑ�����������exe�̖��O��ۑ���������
	
	// �Q�b�^�[
	bool GetbResult();		// �N�����m�F
};