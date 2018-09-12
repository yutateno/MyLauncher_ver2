#pragma once
#include "ProjectBase.hpp"

#include <vector>

#pragma warning(disable : 4996)

class FolderName
{
private:
	char Path[MAX_PATH + 1];	// 実行ファイルの完全パスを取得する変数

	char drive[MAX_PATH + 1]	// ドライブ
		, dir[MAX_PATH + 1]		// ディレクトリパス
		, fname[MAX_PATH + 1]	// ファイル名
		, ext[MAX_PATH + 1];	// ファイル名の拡張子

	int gamenum;		// カレントディレクトリに入れてあるゲームの数

	std::string gamePath;	// ランチャー.exeのパス

	std::string tempPath;	// createPathへ渡すための仮置きのパス保持変数

	std::string createPath;	// ゲームを起動するためのパス


	// 配列数だけゲームの数があり、個々でゲームのLauncherフォルダに入ってるそれぞれの名前を得られる
	std::vector<std::string> foldername;			// ゲームの名前
	std::vector<std::string> moviename;			// 動画の名前
	std::vector<std::string> drawname;			// 画像の名前
	std::vector<std::string> textname;			// テキストの名前


	std::string SearchMediaFile(std::string gamePath, std::string gamefilename, std::string extension);				// ランチャーのためのゲームのメディア類の名前をそれぞれ調べる
	void SearchDrawFile(std::string gamePath, std::string gamefilename, std::string extension);	// 画像用の(ランチャーのためのゲームのメディア類の名前をそれぞれ調べる)
	void SearchGameFile(std::string gamePath);													// ランチャー.exeと同じ階層に入れたゲームのフォルダ名を調べる
	HANDLE hFind;																				// フォルダを確認する
	int fileCount;																				// フォルダの数を得る
	WIN32_FIND_DATA FindFileData;																// 確認したフォルダの名前を得る


public:
	FolderName();		// コンストラクタ
	~FolderName();		// デストラクタ


	// ゲッター
	int GetGameNum();							// ゲームの個数
	std::string GetPathName();						// ゲームのパス
	std::string GetFolderName(int catch_number);		// ゲームのフォルダ名
	std::vector<std::string> GetGameListName();			// ゲームの名前群
	std::vector<std::string> GetMovieListName();			// ゲームの動画群
	std::vector<std::string> GetDrawListName();	// ゲームの画像群
	std::vector<std::string> GetTextListName();			// ゲームのテキスト群
};