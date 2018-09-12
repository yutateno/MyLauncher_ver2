#include "FolderInMedia.hpp"

using namespace std;
namespace pb = projectbase;

string FolderInMedia::ReadText(string textname)
{
	string L_Line;				// 読み込んだ行（1行）
	ifstream L_File;			// 読み込むファイル
	string textdata = "";	// 返り値

	string tempIn;		// 書き込む用の仮置き変数

	L_File.open(textname);		// ファイルオープン

	// ファイル読み込み失敗
	if (L_File.fail())
	{
		//textdata.resize(1);
		textdata =  "テキストデータなし";
	}
	else
	{
		getline(L_File, L_Line);
			
		// 半角だった場合
		tempIn = L_Line.substr(0, L_Line.size());
		textdata = tempIn.c_str();
	}
	// ファイルを閉じる
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<string> drawname, vector<string> textname, int gamenum)
{
	nonedata = LoadGraph("nonedata.png");


	string completePath = "";
	string tempPath = "";


	int tempDraw = -1;


	for (int i = 0; i != gamenum; ++i)
	{
		// ここまで同じことの繰り返しなのでcompletePathに渡す
		completePath = "";
		completePath.operator+= (pathname);
		completePath.operator+= (gamename[i]);
		completePath.operator+= ("\\");
		completePath.operator+= ("Launcher");
		completePath.operator+= ("\\");


		// 素材ごとにtempPathに文字列を増やさせるようにする
		tempPath = completePath;


		// 動画の読み込み
		tempPath.operator+= (moviename[i]);
		d_movie.push_back(LoadGraph(tempPath.c_str()));
		// 動画がなかった場合nonedataを入れる
		if (d_movie[i] == -1)
		{
			d_movie[i] = nonedata;
		}


		// 画像の読み込み
		tempPath = completePath;
		tempPath.operator+= (drawname[i]);
		d_draw.push_back(LoadGraph(tempPath.c_str()));
		// データがなかった場合そこにnonedataを入れる
		if (d_draw[i] == -1)
		{
			d_draw[i] = nonedata;
		}


		// テキストデータの読み込み
		tempPath = completePath;
		tempPath.operator+= (textname[i]);
		d_text.push_back(ReadText(tempPath));
	}
}

FolderInMedia::~FolderInMedia()
{
	d_draw.clear();
	d_draw.shrink_to_fit();

	d_movie.clear();
	d_movie.shrink_to_fit();

	d_text.clear();
	d_text.shrink_to_fit();

	DeleteGraph(nonedata);
}

int FolderInMedia::GetMovie(int listnum)
{
	return d_movie[listnum];
}

int FolderInMedia::GetDraw(int listnum)
{
	return d_draw[listnum];
}

string FolderInMedia::GetText(int listnum)
{
	return d_text[listnum];
}
