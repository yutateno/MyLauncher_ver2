#pragma once
#include "FolderName.hpp"
#include "FolderInGame.hpp"
#include "FolderInMedia.hpp"
#include "Input.hpp"

class GameList
{
private:
	/// ポインターたち------------------------------------------

	// FolderNameの実態(ゲームを所持するフォルダの名前を持つ)
	FolderName* p_folder_name;		

	// FolderInGameの実態(フォルダのゲームの起動に関する)
	FolderInGame* p_folder_game;	

	// FolderInMediaの実態(フォルダのゲームのメディアに関する)
	FolderInMedia* p_folder_media;	


	// 変えれるウィンドウのサイズ
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


	/// 画像を保存する変数--------------------------

	// ウィンドウサイズに関する画像
	int drawWindow[10];			

	// ウィンドウサイズの決定に関する画像
	int drawSelectWin;			

	// ゲーム起動に関する画像
	int drawGameReady[4];		

	// ランチャーの終了に関する画像
	int drawLauncherEnd[4];		


	/// ゲーム一覧に関する-----------------

	// 遊べるゲームの数
	int gameNum;			

	// 今見ているゲーム
	int now_checkGame;		

	// 今選択しているゲームの列
	int selectSideNum;		
	
	
	/// ゲームの起動に関する------------

	// ゲーム起動の確認
	bool gameReady;			

	// ゲーム起動の選択
	bool gameReadyCheck;	

	// ゲームを起動しているか
	bool createGameFlag;	


	/// ランチャー終了に関する------------------------------------------------

	// ランチャーを終了させる
	bool launcher_end;			

	// 終了コマンドを入力されたかどうか
	bool endFlag;				

	// 終了確認画面での終了確認
	bool endComfirm;			

	// ランチャー終了コマンドかオプションコマンドにカーソルを当てているか
	bool endCommandForcus;		

	// 強制終了させるかどうか
	bool forceEnd;			

	// 強制終了の確認画面の表示時間
	int forceEndCount;		


	/// ウィンドウサイズ変更に関する------------------------

	// あなたのディスプレイ標準ウィンドウのXサイズ
	int default_xSize;			

	// あなたのディスプレイ標準ウィンドウのYサイズ
	int default_ySize;			

	// 今の指定サイズ
	int numSize;				

	// サイズ変更後のXサイズ
	int xSize;					

	// サイズ変更後のYサイズ
	int ySize;					

	// ゲームを選択している(上のオプションではない)
	bool gameSelect;			

	// ウィンドウサイズ変更メニューの表示フラッグ
	bool windowSizeMenuFlag;	

	// ウィンドウサイズのforループ数値のためのもの
	int optionTextFor;			

	// ウィンドウサイズオプションの演出用変数
	int optionPerformerCount;
	/// --------------------------------------------------	


	/// 操作に関する-------------------------------------------------------

	// ダブルクリックをさせない(複数のデバイスから同時に取得しているため)
	int doubleSelectWait;		

	

	/// 描画のプロセス------------------------

	// ゲーム起動に関する描画
	void DrawGameFileScroll();		

	// オプションに関する描画
	void DrawOption();				


	/// 操作のプロセス---------------------------------------------------------------

	// 入力
	void KeyProcess();																	

	// オプションの操作に関する
	void OptionKeyProcess(int right, int left, int up, int down, int dicision);			

	// ゲーム起動の操作に関する
	void GameUpdate(int right, int left, int dicision);								

	// ランチャー終了の操作に関する
	void LauncherEnd(int left, int right, int dicision);


public:
	GameList(int defaultXSize, int defaultYSize);		// コンストラクタ
	~GameList();										// デストラクタ


	void Draw();		// 描画
	void Process();		// メイン


	// ゲッター
	bool GetCreateGame();		// ゲームの起動
	bool GetLauncherEnd();		// ランチャーの終了
};