#pragma once
#include "FolderName.h"
#include "FolderInGame.h"
#include "FolderInMedia.h"
#include "input.h"

class GameList
{
private:
	FolderName * folder_name;		// FolderNameの実態(ゲームを所持するフォルダの名前を持つ)
	FolderInGame * folder_game;		// FolderInGameの実態(フォルダのゲームの起動に関する)
	FolderInMedia * folder_media;	// FolderInMediaの実態(フォルダのゲームのメディアに関する)

	int s_bgm;				// 飽きたように流すBGM(使わないかも)

	int gamenum;			// ゲームを所有する個数

	int now_checkgame;		// 今見ているゲーム

	int gameReadyWait;		// 同じコマンドを押させたい

	int fontData;			// 作成するフォントデータ

	bool gameReady;			// ゲーム起動の確認

	bool gameReadyCheck;	// ゲーム起動の選択

	bool createGameFlag;	// ゲームを起動しているか

	bool launcher_end;		// ランチャーを終了させる

	int moviecount;			// 次の動画へ移るカウント

	void KeyAtach(int right, int left, int dicision);

public:
	GameList();		// コンストラクタ
	~GameList();	// デストラクタ

	void Draw();		// 描画
	void Process();		// メイン
	void KeyProcess();	// 入力

	// ゲッター
	bool GetCreateGame();		// ゲームの起動
	bool GetLauncherEnd();		// ランチャーの終了
};