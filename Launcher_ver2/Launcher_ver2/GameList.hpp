#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	FolderName* p_folder_name;		// FolderNameの実態(ゲームを所持するフォルダの名前を持つ)
	FolderInGame* p_folder_game;		// FolderInGameの実態(フォルダのゲームの起動に関する)
	FolderInMedia* p_folder_media;	// FolderInMediaの実態(フォルダのゲームのメディアに関する)

	int gamenum;			// ゲームを所有する個数

	int now_checkgame;		// 今見ているゲーム

	int gameReadyWait;		// 同じコマンドを押させたい

	int fontData;			// 作成するフォントデータ

	bool gameReady;			// ゲーム起動の確認

	bool gameReadyCheck;	// ゲーム起動の選択

	bool createGameFlag;	// ゲームを起動しているか

	bool launcher_end;		// ランチャーを終了させる

	void GameUpdate(int right, int left, int dicision);


	// 変えれるウィンドウのサイズ(XとY両方持つ奴欲しかった)(本当はenumの数値にX座標入れてfor回したかったけど出来ないから妥協)
	struct SizeWindow {
		enum Select
		{
			Default,		// 一応、特に意味はない
			First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth,
		};
		Select type;

		SizeWindow(Select v) : type(v) {}
		operator enum Select() { return type; }

		static int SelectX(int x)
		{
			switch (x)
			{
			case First:		return 640;
			case Second:	return 768;
			case Third:		return 1024;
			case Fourth:	return 1280;
			case Fifth:		return 1366;
			case Sixth:		return 1920;
			case Seventh:	return 2048;
			case Eighth:	return 2560;
			case Ninth:		return 3200;
			default:		return 1;		// 一応、特に意味はない
			}
		}

		static int SelectY(int y)
		{
			switch (y)
			{
			case First:		return 480;
			case Second:	return 576;
			case Third:		return 768;
			case Fourth:	return 720;
			case Fifth:		return 768;
			case Sixth:		return 1080;
			case Seventh:	return 1536;
			case Eighth:	return 1440;
			case Ninth:		return 2400;
			default:		return 1;		// 一応、特に意味はない
			}
		}
	};

	int default_xSize;		// デフォルトウィンドウのXサイズ
	int default_ySize;		// デフォルトウィンドウのYサイズ

	int numSize;
	int xSize;			// サイズ変更後のXサイズ
	int ySize;			// サイズ変更後のYサイズ

	bool gameSelect;


	int drawWindow[10];

	int drawSelectWin;

	bool windowSizeMenuFlag;	// ウィンドウサイズ変更メニューの表示フラッグ


	int optionTextFor;		// forループ数値のためのもの

	int drawGameReady[4];


	int optionPerformerCount;


	void DrawGameFileScroll();


	void DrawOption();


	int scrollNum;

	int selectSideNum;


	bool endFlag;				// エンドコマンドを入力されたかどうか


	bool endComfirm;			// エンドの確認


	void LauncherEnd();


	void KeyProcess();	// 入力


	int drawLauncherEnd[4];

	bool endOrOption;

public:
	GameList(int defaultXSize, int defaultYSize);		// コンストラクタ
	~GameList();	// デストラクタ


	void Draw();		// 描画
	void Process();		// メイン


	// ゲッター
	bool GetCreateGame();		// ゲームの起動
	bool GetLauncherEnd();		// ランチャーの終了
	bool GetEndFlag();
};