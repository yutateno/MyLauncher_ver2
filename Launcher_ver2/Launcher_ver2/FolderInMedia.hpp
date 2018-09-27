#pragma once
#include "ProjectBase.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	// �t�@�C���̒��g�Ɋւ���
	std::vector<int> v_draw;			// �摜
	std::vector<int> v_movie;			// ����
	std::vector<std::string> v_text;	// �e�L�X�g
	int noneData;						// ���f�B�A�̃f�[�^���Ȃ������ꍇ

	std::string ReadText(std::string textname);		// �e�L�X�g�f�[�^��ǂݍ���


public:
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::string> drawname, std::vector<std::string> textname, int gamenum);	// �R���X�g���N�^
	~FolderInMedia();		// �f�X�g���N�^


	// �Q�b�^�[
	const int GetMovie(const int listnum) const;			// ����
	const int GetDraw(const int listnum) const;				// �摜
	const std::string GetText(const int listnum) const;		// �e�L�X�g
};