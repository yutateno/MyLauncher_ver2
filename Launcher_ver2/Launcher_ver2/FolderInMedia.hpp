#pragma once
#include "ProjectBase.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class FolderInMedia
{
private:
	/// ファイルの中身に関する----------------------

	// 画像
	std::vector<int> v_draw;			

	// 動画
	std::vector<int> v_movie;			

	// テキスト
	std::vector<std::string> v_text;	

	// メディアのデータがなかった場合
	int noneData;						


	// テキストデータを読み込む
	std::string ReadText(std::string textname);		


public:
	// コンストラクタ
	FolderInMedia(std::string pathname, std::vector<std::string> gamename, std::vector<std::string> moviename
		, std::vector<std::string> drawname, std::vector<std::string> textname, int gamenum);	

	// デストラクタ
	~FolderInMedia();		


	/// ゲッター------------------------------------------------

	// 動画
	const int GetMovie(const int listnum) const;			

	// 画像
	const int GetDraw(const int listnum) const;				

	// テキスト
	const std::string GetText(const int listnum) const;		
};