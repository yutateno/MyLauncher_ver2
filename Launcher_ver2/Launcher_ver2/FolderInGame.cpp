#include "FolderInGame.hpp"

void FolderInGame::Process(std::string createPath, std::string folderName)
{
	bResult = TRUE;

	PROCESS_INFORMATION pInfo = {};	// プロセス軌道のためのもの

	STARTUPINFO sInfo = {};			// 初期プロセス起動のためのもの(こっちだけローカルじゃなくていいかも)

	//STARTUPINFO 構造体の内容を取得
	ZeroMemory(&sInfo, sizeof(sInfo));		// 構造体全部初期化する
	sInfo.cb = sizeof(sInfo);

	GetStartupInfo(&sInfo);					// スタートアップ情報を得る

	// 見えない状態で起動させる
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;

	gamePath = "";
	direPath = "";

	gamePath.operator+= (createPath);
	gamePath.operator+= (folderName);
	gamePath.operator+= ("\\");
	direPath = gamePath;
	gamePath.operator+= (folderName);
	gamePath.operator+= (".exe");

	SetWindowMinimizeFlag(TRUE);	// 最小化にする

	bResult = CreateProcess(
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

	CloseHandle(pInfo.hThread);
	WaitForSingleObject(pInfo.hProcess, INFINITE);
	SetWindowMinimizeFlag(FALSE);		// 最小化を解除
	CloseHandle(pInfo.hProcess);
	gamePath = "";
	bResult = FALSE;
}

bool FolderInGame::GetbResult()
{
	return bResult;
}