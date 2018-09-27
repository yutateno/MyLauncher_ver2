#include "FolderInGame.hpp"

void FolderInGame::Process(std::string createPath, std::string folderName)
{
	result = TRUE;		// ゲームの起動を始めた合図


	PROCESS_INFORMATION pInfo = {};	// プロセス軌道のためのもの


	STARTUPINFO sInfo = {};			// 初期プロセス起動のためのもの


	ZeroMemory(&sInfo, sizeof(sInfo));		// 構造体全部初期化する
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));


	GetStartupInfo(&sInfo);					// スタートアップ情報を得る


	// ランチャーが見えない状態で起動させる
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;


	// ディレクトリ位置を調べる用変数
	std::string gamePath = "";				// ゲームexeファイル
	std::string direPath = "";				// ゲームファイル


	gamePath.operator+= (createPath);
	gamePath.operator+= (folderName);
	gamePath.operator+= ("\\");
	direPath = gamePath;
	gamePath.operator+= (folderName);
	gamePath.operator+= (".exe");


	SetWindowMinimizeFlag(TRUE);	// ランチャーを最小化にする


	// ゲームを起動
	result = CreateProcess(
		NULL,
		(LPSTR)gamePath.c_str(),		// ゲームを指定
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_PROCESS_GROUP,
		NULL,
		direPath.c_str(),				// カレントディレクトリを指定
		&sInfo,
		&pInfo
	);


	WaitForSingleObject(pInfo.hProcess, INFINITE);		// 終了するまで待機
	SetWindowMinimizeFlag(FALSE);						// 最小化を解除
	CloseHandle(pInfo.hProcess);						// 解放
	CloseHandle(pInfo.hThread);							// 解放


	result = FALSE;										// ランチャーへの合図
}

bool FolderInGame::GetbResult()
{
	return result;
}