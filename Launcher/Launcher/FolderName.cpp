#include "FolderName.h"

using namespace std;

namespace pb = projectbase;

string FolderName::SearchMediaFile(string gamePath, string gamefilename, string extension)
{
	string media_filename = "";		// 仮置き引数

	// 拡張子を持つファイルの名前を調べる
	gamePath.operator+= (gamefilename);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("launcher");
	gamePath.operator+= ("\\");
	gamePath.operator+= ("*.");
	gamePath.operator+= (extension);

	hFind = FindFirstFile(gamePath.c_str(), &FindFileData);		// ファイルを調べる
	if (hFind != INVALID_HANDLE_VALUE)		// 存在しなかったらやめる
	{
		do {
			// FindFileData.cFileNameがファイル名
			media_filename = FindFileData.cFileName;
		} while (FindNextFile(hFind, &FindFileData));	// 存在し続けるだけ続ける

		FindClose(hFind);
	}

	return media_filename;		// 調べたい拡張子を持つファイルの名前を返す
}

void FolderName::SearchDrawFile(string gamePath, string gamefilename, string extension, int nowlist)
{
	// 拡張子を持つファイルの名前を調べる
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
	fileCount = 0;		// 確認できたファイルの個数を調べる

	gamePath.operator+= ("*.");		// フォルダを調べる

	hFind = FindFirstFile(gamePath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			++fileCount;
			// FindFileData.cFileNameがファイル名
			if (fileCount >= 3)		// [.][..]を避けるため
			{
				foldername.push_back(FindFileData.cFileName);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}

FolderName::FolderName()
{
	GetModuleFileName(NULL, Path, MAX_PATH);	// この実行ファイルの完全パスを取得

	_splitpath(Path, drive, dir, fname, ext);	// パス名を構成要素に分解する

	// 必要なものをいくつか結合していく
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

	drawname.resize(gamenum);		// ゲームの数だけ事前に確保する

	for (int i = 0; i != gamenum; ++i)
	{
		// 動画のファイル名を保存
		moviename.push_back(SearchMediaFile(gamePath, foldername[i], "mp4"));	// mp4以外だと何があるかわかんないからとりあえずこれだけ

		// 画像のファイル名を保存
		// pngを調べる
		SearchDrawFile(gamePath, foldername[i], "png", i);
		// 予定枚数に足らない場合はjpgを調べる
		if (drawname[i].size() != pb::DRAW_MEDIA_NUM)
		{
			SearchDrawFile(gamePath, foldername[i], "jpg", i);
		}

		// テキストデータのファイル名を保存
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