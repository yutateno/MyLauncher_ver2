#pragma once
#include "ProjectBase.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	int g_SizeX;
	int g_SizeY;

	int nonedata;		// メディアのデータがなかった場合

	std::vector<std::vector<int>> d_draw;		// 背景
	std::vector<int> d_movie;			// 動画
	std::vector<std::vector<std::string>> d_text;	// テキスト(処理がめんどくさいため後で)

	std::vector<std::string> ReadText(std::string textname);		// テキストデータを読み込む

public:
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::vector<std::string>> drawname, std::vector<std::string> textname, int gamenum);	// コンストラクタ
	~FolderInMedia();		// デストラクタ

	// ゲッター
	int GetMovie(int listnum);
	std::vector<int> GetDraw(int listnum);
	std::vector<std::string> GetText(int listnum);
};