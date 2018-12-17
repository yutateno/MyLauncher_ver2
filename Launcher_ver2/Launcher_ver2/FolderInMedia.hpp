#pragma once
#include "ProjectBase.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	/// �t�@�C���̒��g�Ɋւ���----------------------

	// �摜
	std::vector<int> v_draw;			

	// ����
	std::vector<int> v_movie;			

	// �e�L�X�g
	std::vector<std::string> v_text;	

	// ���f�B�A�̃f�[�^���Ȃ������ꍇ
	int noneData;						


	// �e�L�X�g�f�[�^��ǂݍ���
	std::string ReadText(std::string textname);		


public:
	// �R���X�g���N�^
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::string> drawname, std::vector<std::string> textname, int gamenum);	

	// �f�X�g���N�^
	~FolderInMedia();		


	/// �Q�b�^�[------------------------------------------------

	// ����
	const int GetMovie(const int listnum) const;			

	// �摜
	const int GetDraw(const int listnum) const;				

	// �e�L�X�g
	const std::string GetText(const int listnum) const;		
};