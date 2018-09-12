#pragma once
#include "ProjectBase.h"

class FolderInGame
{
private:
	BOOL bResult;		// プロセスが起動したかどうか

	std::string gamePath;	// ゲームのパス
	std::string direPath;	// ディレクトリのパス

public:
	FolderInGame() : bResult(FALSE) {}		// コンストラクタ
	~FolderInGame() {}	// デストラクタ

	void Process(std::string createPath, std::string folderName);		// メイン/ exeの階層までのパスを保存した引数とexeの名前を保存した引数
	
	// ゲッター
	bool GetbResult();		// 起動を確認
};