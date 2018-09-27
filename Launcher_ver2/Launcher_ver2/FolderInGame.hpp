#pragma once
#include "ProjectBase.hpp"

class FolderInGame
{
private:
	BOOL result;		// プロセスが起動したかどうか


public:
	FolderInGame() : result(FALSE) {}		// コンストラクタ
	~FolderInGame() {}	// デストラクタ


	void Process(std::string createPath, std::string folderName);		// メイン/ exeの階層までのパスを保存した引数とexeの名前を保存した引数


	// ゲッター
	bool GetbResult();		// 起動を確認
};