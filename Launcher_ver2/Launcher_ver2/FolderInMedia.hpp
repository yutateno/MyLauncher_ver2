#pragma once
#include "ProjectBase.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	// ファイルの中身に関する
	std::vector<int> v_draw;			// 画像
	std::vector<int> v_movie;			// 動画
	std::vector<std::string> v_text;	// テキスト
	int noneData;						// メディアのデータがなかった場合

	std::string ReadText(std::string textname);		// テキストデータを読み込む


public:
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::string> drawname, std::vector<std::string> textname, int gamenum);	// コンストラクタ
	~FolderInMedia();		// デストラクタ


	// ゲッター
	const int GetMovie(const int listnum) const;			// 動画
	const int GetDraw(const int listnum) const;				// 画像
	const std::string GetText(const int listnum) const;		// テキスト
};