#include "FolderInMedia.h"

using namespace std;
namespace pb = projectbase;

vector<string> FolderInMedia::ReadText(string textname)
{
	int L_Count = 0;			// 読み込み用（何行目を読み込んでいるか
	string L_Line;				// 読み込んだ行（1行）
	ifstream L_File;			// 読み込むファイル
	vector<string> textdata;	// 返り値

	int num = 0;		// １行の文字数
	string tempIn;		// 書き込む用の仮置き変数
	int lineNum = 0;	// 書き込み文字の初期位置

	L_File.open(textname);		// ファイルオープン

	// ファイル読み込み失敗
	if (L_File.fail())
	{
		textdata.resize(L_Count + 1);
		textdata[L_Count].operator+= ("テキストデータなし");
	}
	else
	{
		// 一行ずつ読み込み
		while (getline(L_File, L_Line))
		{	
			textdata.resize(L_Count + 6);		// 横の長さでは改行を何回かさせるので多めに生成しとく
			num = 0;
			lineNum = 0;

			for (int i = 0; i != L_Line.size(); ++i)
			{
				num++;
				// 文字がテキストボックスをはみ出す
				if (num >= pb::TEXT_X_NUM)
				{
					// 半角だった場合
					if (IsDBCSLeadByte(L_Line[i]) == 0)
					{
						tempIn = L_Line.substr(lineNum, i - lineNum);
						lineNum = i - 1;
						num = 0;
					}
					else
					{
						tempIn = L_Line.substr(lineNum, i - lineNum);
						lineNum = i;
						num = 0;
					}
					textdata[L_Count].operator+= (tempIn.c_str());
					L_Count++;	// 次の行に
				}
			}
			tempIn = L_Line.substr(lineNum, L_Line.size() - lineNum);
			textdata[L_Count].operator+= (tempIn.c_str());

			L_Count++;	// 次の行に

		}
	}
	// ファイルを閉じる
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<vector<string>> drawname, vector<string> textname, int gamenum)
{
	nonedata = LoadGraph("nonedata.png");

	string completePath = "";
	string tempPath = "";

	int tempDraw = -1;
	int tempDrawIn[4];

	d_draw.resize(gamenum);		// 読み込み数だけ確保

	for (int i = 0; i != gamenum; ++i)
	{
		for (int j = 0; j != pb::DRAW_MEDIA_NUM; ++j)
		{
			tempDrawIn[j] = -1;
		}

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
		for (int j = 0; j != drawname[i].size(); ++j)
		{
			tempPath = completePath;
			tempPath.operator+= (drawname[i][j]);
			tempDraw= LoadGraph(tempPath.c_str());
			GetGraphSize(tempDraw, &g_SizeX, &g_SizeY);		// 素材の大きさを調べる
			// 素材の大きさで「背景」「テキストボックス」「タイトルロゴ」を判断
			if (g_SizeY >= pb::WINDOW_Y - 5)
			{
				tempDrawIn[0] = tempDraw;
			}
			else if (g_SizeY < pb::WINDOW_Y - 5 && g_SizeY >= pb::TEXT_BOX_LAST_Y - pb::TEXT_BOX_FIRST_Y - 5)
			{
				tempDrawIn[2] = tempDraw;
			}
			else if (g_SizeY < pb::TEXT_BOX_LAST_Y - pb::TEXT_BOX_FIRST_Y - 5 && g_SizeY >= pb::DRAW_GAMECHECK_SIZE_Y - 5)
			{
				tempDrawIn[3] = tempDraw;
			}
			else
			{
				tempDrawIn[1] = tempDraw;
			}
		}
		for (int j = 0; j != pb::DRAW_MEDIA_NUM; ++j)
		{
			// データがなかった場合そこにnonedataを入れる
			if (tempDrawIn[j] == -1)
			{
				tempDrawIn[j] = nonedata;
			}
			d_draw[i].push_back(tempDrawIn[j]);
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

vector<int> FolderInMedia::GetDraw(int listnum)
{
	return d_draw[listnum];
}

vector<string> FolderInMedia::GetText(int listnum)
{
	return d_text[listnum];
}
