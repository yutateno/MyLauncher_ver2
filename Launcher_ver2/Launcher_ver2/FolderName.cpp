#include "FolderName.hpp"

using namespace std;


// �t�@�C���̒��g�T��
string FolderName::SearchMediaFile(string gamePath, string gamefilename, string extension)
{
	string media_filename = "";		// ���u������


	WIN32_FIND_DATA findFileData;
	ZeroMemory(&findFileData, sizeof(WIN32_FIND_DATA));		// ������


	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	gamePath.operator+= (gamefilename);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("launcher");
	gamePath.operator+= ("\\");
	gamePath.operator+= ("*.");
	gamePath.operator+= (extension);


	HANDLE hFind = FindFirstFile(gamePath.c_str(), &findFileData);		// �t�@�C���𒲂ׂ�
	if (hFind != INVALID_HANDLE_VALUE)		// ���݂��Ȃ��������߂�
	{
		// FindFileData.cFileName���t�@�C����
		media_filename = findFileData.cFileName;
	}
	FindClose(hFind);

	return media_filename;		// ���ׂ����g���q�����t�@�C���̖��O��Ԃ�
}


// �Q�[���t�@�C���T��
void FolderName::SearchGameFile(string gamePath)
{
	int fileCount = 0;		// �m�F�ł����t�@�C���̌��𒲂ׂ�

	WIN32_FIND_DATA findFileData;
	ZeroMemory(&findFileData, sizeof(WIN32_FIND_DATA));

	gamePath.operator+= ("*.");		// �t�H���_�𒲂ׂ�

	HANDLE hFind = FindFirstFile(gamePath.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			// FindFileData.cFileName���t�@�C����
			if (++fileCount >= 3)		// [.][..]������邽��
			{
				v_folderName.push_back(findFileData.cFileName);
			}
		} while (FindNextFile(hFind, &findFileData));
	}
	FindClose(hFind);
}


// �R���X�g���N�^
FolderName::FolderName()
{
	// vector�̒��g���ꉞ������
	v_drawName.clear();
	v_folderName.clear();
	v_movieName.clear();
	v_textName.clear();


	GetModuleFileName(NULL, Path, MAX_PATH);	// ���̎��s�t�@�C���̊��S�p�X���擾

	_splitpath(Path, drive, dir, fname, ext);	// �p�X�����\���v�f�ɕ�������


	// �K�v�Ȃ��̂��������������Ă���
	gamePath = "";

	gamePath.operator+= (drive);
	gamePath.operator+= (dir);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("game");
	gamePath.operator+= ("\\");


	SearchGameFile(gamePath);				// �Q�[���t�@�C���𒲂ׂ�


	for (int i = 0; i != static_cast<int>(v_folderName.size()); ++i)
	{
		// ����̃t�@�C������ۑ�
		v_movieName.push_back(SearchMediaFile(gamePath, v_folderName[i], "mp4"));

		// �摜�̃t�@�C������ۑ�
		v_drawName.push_back(SearchMediaFile(gamePath, v_folderName[i], "png"));

		// �e�L�X�g�f�[�^�̃t�@�C������ۑ�
		v_textName.push_back(SearchMediaFile(gamePath, v_folderName[i], "txt"));
	}
}


// �f�X�g���N�^
FolderName::~FolderName()
{
	VECTOR_RELEASE(v_folderName);
	VECTOR_RELEASE(v_movieName);
	VECTOR_RELEASE(v_drawName);
	VECTOR_RELEASE(v_textName);
}



const int FolderName::GetGameNum() const
{
	return static_cast<int>(v_folderName.size());
}

const string FolderName::GetPathName() const
{
	return gamePath;
}

const string FolderName::GetFolderName(const int catch_number) const
{
	return v_folderName[catch_number];
}

const vector<string> FolderName::GetGameListName() const
{
	return v_folderName;
}

const vector<string> FolderName::GetMovieListName() const
{
	return v_movieName;
}


const vector<string> FolderName::GetDrawListName() const
{
	return v_drawName;
}


const vector<string> FolderName::GetTextListName() const
{
	return v_textName;
}