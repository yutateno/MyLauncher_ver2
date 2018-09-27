#include "FolderInMedia.hpp"

using namespace std;

string FolderInMedia::ReadText(string textname)
{
	string L_Line = "";				// 読み込んだ行（1行）
	ifstream L_File;			// 読み込むファイル
	string textdata = "";	// 返り値

	string tempIn;		// 書き込む用の仮置き変数

	L_File.open(textname);		// ファイルオープン

	// ファイル読み込み失敗
	if (L_File.fail())
	{
		textdata.resize(1);
		textdata =  "テキストデータなし";
	}
	else
	{
		getline(L_File, L_Line);
		
		tempIn = L_Line.substr(0, L_Line.size());
		textdata = tempIn.c_str();
	}
	// ファイルを閉じる
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<string> drawname, vector<string> textname, int gamenum)
{
	// vectorの一応初期化
	v_draw.clear();
	v_movie.clear();
	v_text.clear();

	noneData = LoadGraph("nonedata.png");


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
		v_movie.push_back(LoadGraph(tempPath.c_str()));
		// 動画がなかった場合nonedataを入れる
		if (v_movie[i] == -1)
		{
			v_movie[i] = noneData;
		}


		// 画像の読み込み
		tempPath = completePath;
		tempPath.operator+= (drawname[i]);
		v_draw.push_back(LoadGraph(tempPath.c_str()));
		// データがなかった場合そこにnonedataを入れる
		if (v_draw[i] == -1)
		{
			v_draw[i] = noneData;
		}


		// テキストデータの読み込み
		tempPath = completePath;
		tempPath.operator+= (textname[i]);
		v_text.push_back(ReadText(tempPath));
	}
}

FolderInMedia::~FolderInMedia()
{
	VECTOR_RELEASE(v_draw);
	VECTOR_RELEASE(v_movie);
	VECTOR_RELEASE(v_text);

	GRAPHIC_RELEASE(noneData);
}

const int FolderInMedia::GetMovie(const int listnum) const
{
	return v_movie[listnum];
}

const int FolderInMedia::GetDraw(const int listnum) const
{
	return v_draw[listnum];
}

const string FolderInMedia::GetText(const int listnum) const
{
	return v_text[listnum];
}
