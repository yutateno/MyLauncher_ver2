#pragma once
#include "ProjectBase.hpp"

class FolderInGame
{
private:
	BOOL result;		// �v���Z�X���N���������ǂ���


public:
	FolderInGame() : result(FALSE) {}		// �R���X�g���N�^
	~FolderInGame() {}	// �f�X�g���N�^


	void Process(std::string createPath, std::string folderName);		// ���C��/ exe�̊K�w�܂ł̃p�X��ۑ�����������exe�̖��O��ۑ���������


	// �Q�b�^�[
	bool GetbResult();		// �N�����m�F
};