#include "FolderName.hpp"

using namespace std;


// ファイルの中身探索
string FolderName::SearchMediaFile(string gamePath, string gamefilename, string extension)
{
	string media_filename = "";		// 仮置き引数


	WIN32_FIND_DATA findFileData;
	ZeroMemory(&findFileData, sizeof(WIN32_FIND_DATA));		// 初期化


	// 拡張子を持つファイルの名前を調べる
	gamePath.operator+= (gamefilename);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("launcher");
	gamePath.operator+= ("\\");
	gamePath.operator+= ("*.");
	gamePath.operator+= (extension);


	HANDLE hFind = FindFirstFile(gamePath.c_str(), &findFileData);		// ファイルを調べる
	if (hFind != INVALID_HANDLE_VALUE)		// 存在しなかったらやめる
	{
		// FindFileData.cFileNameがファイル名
		media_filename = findFileData.cFileName;
	}
	FindClose(hFind);

	return media_filename;		// 調べたい拡張子を持つファイルの名前を返す
}


// ゲームファイル探索
void FolderName::SearchGameFile(string gamePath)
{
	int fileCount = 0;		// 確認できたファイルの個数を調べる

	WIN32_FIND_DATA findFileData;
	ZeroMemory(&findFileData, sizeof(WIN32_FIND_DATA));

	gamePath.operator+= ("*.");		// フォルダを調べる

	HANDLE hFind = FindFirstFile(gamePath.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			// FindFileData.cFileNameがファイル名
			if (++fileCount >= 3)		// [.][..]を避けるため
			{
				v_folderName.push_back(findFileData.cFileName);
			}
		} while (FindNextFile(hFind, &findFileData));
	}
	FindClose(hFind);
}


// コンストラクタ
FolderName::FolderName()
{
	// vectorの中身を一応初期化
	v_drawName.clear();
	v_folderName.clear();
	v_movieName.clear();
	v_textName.clear();


	GetModuleFileName(NULL, Path, MAX_PATH);	// この実行ファイルの完全パスを取得

	_splitpath(Path, drive, dir, fname, ext);	// パス名を構成要素に分解する


	// 必要なものをいくつか結合していく
	gamePath = "";

	gamePath.operator+= (drive);
	gamePath.operator+= (dir);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("game");
	gamePath.operator+= ("\\");


	SearchGameFile(gamePath);				// ゲームファイルを調べる


	for (int i = 0; i != static_cast<int>(v_folderName.size()); ++i)
	{
		// 動画のファイル名を保存
		v_movieName.push_back(SearchMediaFile(gamePath, v_folderName[i], "mp4"));

		// 画像のファイル名を保存
		v_drawName.push_back(SearchMediaFile(gamePath, v_folderName[i], "png"));

		// テキストデータのファイル名を保存
		v_textName.push_back(SearchMediaFile(gamePath, v_folderName[i], "txt"));
	}
}


// デストラクタ
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