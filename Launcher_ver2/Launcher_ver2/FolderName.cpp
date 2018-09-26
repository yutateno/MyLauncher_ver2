#include "FolderName.hpp"

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


void FolderName::SearchDrawFile(string gamePath, string gamefilename, string extension)
{
	//// �g���q�����t�@�C���̖��O�𒲂ׂ�
	//gamePath.operator+= (gamefilename);
	//gamePath.operator+= ("\\");
	//gamePath.operator+= ("launcher");
	//gamePath.operator+= ("\\");
	//gamePath.operator+= ("*.");
	//gamePath.operator+= (extension);

	//hFind = FindFirstFile(gamePath.c_str(), &FindFileData);
	//if (hFind != INVALID_HANDLE_VALUE)
	//{
	//	do {
	//		drawname.push_back(FindFileData.cFileName);
	//	} while (FindNextFile(hFind, &FindFileData));

	//	FindClose(hFind);
	//}
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

	for (int i = 0; i != gamenum; ++i)
	{
		// ����̃t�@�C������ۑ�
		moviename.push_back(SearchMediaFile(gamePath, foldername[i], "mp4"));	// mp4�ȊO���Ɖ������邩�킩��Ȃ�����Ƃ肠�������ꂾ��

		// �摜�̃t�@�C������ۑ�
		drawname.push_back(SearchMediaFile(gamePath, foldername[i], "png"));

		// �e�L�X�g�f�[�^�̃t�@�C������ۑ�
		textname.push_back(SearchMediaFile(gamePath, foldername[i], "txt"));
	}
}


FolderName::~FolderName()
{
	VECTOR_RELEASE(foldername);
	VECTOR_RELEASE(moviename);
	VECTOR_RELEASE(drawname);
	VECTOR_RELEASE(textname);
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


vector<string> FolderName::GetDrawListName()
{
	return drawname;
}


vector<string> FolderName::GetTextListName()
{
	return textname;
}