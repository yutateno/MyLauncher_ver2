#pragma once
#include "ProjectBase.hpp"

class FolderInGame
{
private:
	// �v���Z�X���N���������ǂ���
	BOOL result;		


public:
	// �R���X�g���N�^
	FolderInGame() : result(FALSE) {}		

	// �f�X�g���N�^
	~FolderInGame() {}	


	// ���C��/ exe�̊K�w�܂ł̃p�X��ۑ�����������exe�̖��O��ۑ���������
	void Process(std::string createPath, std::string folderName);		


	/// �Q�b�^�[

	// �N�����m�F
	bool GetbResult();		
};