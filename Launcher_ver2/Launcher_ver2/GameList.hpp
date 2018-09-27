#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	// ポインターたち
	FolderName* p_folder_name;		// FolderNameの実態(ゲームを所持するフォルダの名前を持つ)
	FolderInGame* p_folder_game;		// FolderInGameの実態(フォルダのゲームの起動に関する)
	FolderInMedia* p_folder_media;	// FolderInMediaの実態(フォルダのゲームのメディアに関する)


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


	// 画像を保存する変数
	int drawWindow[10];			// ウィンドウサイズに関する画像
	int drawSelectWin;			// ウィンドウサイズの決定に関する画像
	int drawGameReady[4];		// ゲーム起動に関する画像
	int drawLauncherEnd[4];		// ランチャーの終了に関する画像


	// ゲーム一覧に関する
	int gameNum;			// 遊べるゲームの数
	int now_checkGame;		// 今見ているゲーム
	int selectSideNum;		// 今選択しているゲームの列
	
	
	// ゲームの起動に関する
	bool gameReady;			// ゲーム起動の確認
	bool gameReadyCheck;	// ゲーム起動の選択
	bool createGameFlag;	// ゲームを起動しているか


	// ランチャー終了に関する
	bool launcher_end;			// ランチャーを終了させる
	bool endFlag;				// 終了コマンドを入力されたかどうか
	bool endComfirm;			// 終了確認画面での終了確認
	bool endCommandForcus;		// ランチャー終了コマンドかオプションコマンドにカーソルを当てているか
	bool forceEnd;				// 強制終了させるかどうか


	// ウィンドウサイズ変更に関する
	int default_xSize;			// あなたのディスプレイ標準ウィンドウのXサイズ
	int default_ySize;			// あなたのディスプレイ標準ウィンドウのYサイズ
	int numSize;				// 今の指定サイズ
	int xSize;					// サイズ変更後のXサイズ
	int ySize;					// サイズ変更後のYサイズ
	bool gameSelect;			// ゲームを選択している(上のオプションではない)
	bool windowSizeMenuFlag;	// ウィンドウサイズ変更メニューの表示フラッグ
	int optionTextFor;			// ウィンドウサイズのforループ数値のためのもの

	

	// 描画のプロセス
	void DrawGameFileScroll();		// ゲーム起動に関する描画
	void DrawOption();				// オプションに関する描画


	// 操作のプロセス
	void KeyProcess();																	// 入力
	void OptionKeyProcess(int right, int left, int up, int down, int dicision);			// オプションの操作に関する
	void GameUpdate(int right, int left, int dicision);									// ゲーム起動の操作に関する
	void LauncherEnd(int left, int right, int dicision);								// ランチャー終了の操作に関する

public:
	GameList(int defaultXSize, int defaultYSize);		// コンストラクタ
	~GameList();	// デストラクタ


	void Draw();		// 描画
	void Process();		// メイン


	// ゲッター
	bool GetCreateGame();		// ゲームの起動
	bool GetLauncherEnd();		// ランチャーの終了
};