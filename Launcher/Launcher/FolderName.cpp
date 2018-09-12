#include "FolderName.h"

using namespace std;

namespace pb = projectbase;

string FolderName::SearchMediaFile(string gamePath, string gamefilename, string extension)
{
	string media_filename = "";		// ���u������

	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	gamePath.operator+= (gamefilename);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("launcher");
	gamePath.operator+= ("\\");
	gamePath.operator+= ("*.");
	gamePath.operator+= (extension);

	hFind = FindFirstFile(gamePath.c_str(), &FindFileData);		// �t�@�C���𒲂ׂ�
	if (hFind != INVALID_HANDLE_VALUE)		// ���݂��Ȃ��������߂�
	{
		do {
			// FindFileData.cFileName���t�@�C����
			media_filename = FindFileData.cFileName;
		} while (FindNextFile(hFind, &FindFileData));	// ���݂������邾��������

		FindClose(hFind);
	}

	return media_filename;		// ���ׂ����g���q�����t�@�C���̖��O��Ԃ�
}

void FolderName::SearchDrawFile(string gamePath, string gamefilename, string extension, int nowlist)
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	gamePath.operator+= (gamefilename);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("launcher");
	gamePath.operator+= ("\\");
	gamePath.operator+= ("*.");
	gamePath.operator+= (extension);

	hFind = FindFirstFile(gamePath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			drawname[nowlist].push_back(FindFileData.cFileName);
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}

void FolderName::SearchGameFile(string gamePath)
{
	fileCount = 0;		// �m�F�ł����t�@�C���̌��𒲂ׂ�

	gamePath.operator+= ("*.");		// �t�H���_�𒲂ׂ�

	hFind = FindFirstFile(gamePath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			++fileCount;
			// FindFileData.cFileName���t�@�C����
			if (fileCount >= 3)		// [.][..]������邽��
			{
				foldername.push_back(FindFileData.cFileName);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}

FolderName::FolderName()
{
	GetModuleFileName(NULL, Path, MAX_PATH);	// ���̎��s�t�@�C���̊��S�p�X���擾

	_splitpath(Path, drive, dir, fname, ext);	// �p�X�����\���v�f�ɕ�������

	// �K�v�Ȃ��̂��������������Ă���
	gamePath = "";

	gamePath.operator+= (drive);
	gamePath.operator+= (dir);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("game");
	gamePath.operator+= ("\\");

	SearchGameFile(gamePath);

	gamenum = foldername.size();

	tempPath = "";

	tempPath.operator+= (drive);
	tempPath.operator+= (dir);
	tempPath.operator+= ("\\");
	tempPath.operator+= ("game");
	tempPath.operator+= ("\\");

	createPath = tempPath;

	drawname.resize(gamenum);		// �Q�[���̐��������O�Ɋm�ۂ���

	for (int i = 0; i != gamenum; ++i)
	{
		// ����̃t�@�C������ۑ�
		moviename.push_back(SearchMediaFile(gamePath, foldername[i], "mp4"));	// mp4�ȊO���Ɖ������邩�킩��Ȃ�����Ƃ肠�������ꂾ��

		// �摜�̃t�@�C������ۑ�
		// png�𒲂ׂ�
		SearchDrawFile(gamePath, foldername[i], "png", i);
		// �\�薇���ɑ���Ȃ��ꍇ��jpg�𒲂ׂ�
		if (drawname[i].size() != pb::DRAW_MEDIA_NUM)
		{
			SearchDrawFile(gamePath, foldername[i], "jpg", i);
		}

		// �e�L�X�g�f�[�^�̃t�@�C������ۑ�
		textname.push_back(SearchMediaFile(gamePath, foldername[i], "txt"));
	}
}

FolderName::~FolderName()
{	
	foldername.clear();
	foldername.shrink_to_fit();

	moviename.clear();
	moviename.shrink_to_fit();

	drawname.clear();
	drawname.shrink_to_fit();

	textname.clear();
	textname.shrink_to_fit();
}

int FolderName::GetGameNum()
{
	return gamenum;
}

string FolderName::GetPathName()
{
	return createPath;
}

string FolderName::GetFolderName(int catch_number)
{
	return foldername[catch_number];
}

vector<string> FolderName::GetGameListName()
{
	return foldername;
}

vector<string> FolderName::GetMovieListName()
{
	return moviename;
}

vector<vector<string>> FolderName::GetDrawListName()
{
	return drawname;
}

vector<string> FolderName::GetTextListName()
{
	return textname;
}