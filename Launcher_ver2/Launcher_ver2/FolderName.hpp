#pragma once
#include "ProjectBase.hpp"

#include <vector>

#pragma warning(disable : 4996)

class FolderName
{
private:
	// ランチャーのパスに関する
	char Path[MAX_PATH + 1];	// 実行ファイルの完全パスを取得する変数

	char drive[MAX_PATH + 1]	// ドライブ
		, dir[MAX_PATH + 1]		// ディレクトリパス
		, fname[MAX_PATH + 1]	// ファイル名
		, ext[MAX_PATH + 1];	// ファイル名の拡張子
	
	std::string gamePath;		// ランチャー.exeのパス


	// ゲームファイル内部に関する
	std::vector<std::string> v_folderName;		// ゲームの名前
	std::vector<std::string> v_movieName;		// 動画の名前
	std::vector<std::string> v_drawName;		// 画像の名前
	std::vector<std::string> v_textName;		// テキストの名前


	// ゲームファイルを探索に関する
	std::string SearchMediaFile(std::string gamePath, std::string gamefilename, std::string extension);				// ランチャーのためのゲームのメディア類の名前をそれぞれ調べる
	void SearchGameFile(std::string gamePath);																		// ランチャー.exeと同じ階層に入れたゲームのフォルダ名を調べる
	

public:
	FolderName();		// コンストラクタ
	~FolderName();		// デストラクタ


	// ゲッター
	const int GetGameNum() const;									// ゲームの個数
	const std::string GetPathName() const;							// ゲームのパス
	const std::string GetFolderName(const int catch_number) const;	// ゲームのフォルダ名
	const std::vector<std::string> GetGameListName() const;			// ゲームの名前群
	const std::vector<std::string> GetMovieListName() const;		// ゲームの動画群
	const std::vector<std::string> GetDrawListName() const;			// ゲームの画像群
	const std::vector<std::string> GetTextListName() const;			// ゲームのテキスト群
};