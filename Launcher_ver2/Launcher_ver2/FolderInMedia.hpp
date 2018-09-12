#pragma once
#include "ProjectBase.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	int g_SizeX;
	int g_SizeY;

	int nonedata;		// ���f�B�A�̃f�[�^���Ȃ������ꍇ

	std::vector<int> d_draw;		// �w�i
	std::vector<int> d_movie;			// ����
	std::vector<std::string> d_text;	// �e�L�X�g(�������߂�ǂ��������ߌ��)

	std::string ReadText(std::string textname);		// �e�L�X�g�f�[�^��ǂݍ���

public:
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::string> drawname, std::vector<std::string> textname, int gamenum);	// �R���X�g���N�^
	~FolderInMedia();		// �f�X�g���N�^


	// �Q�b�^�[
	int GetMovie(int listnum);
	int GetDraw(int listnum);
	std::string GetText(int listnum);
};