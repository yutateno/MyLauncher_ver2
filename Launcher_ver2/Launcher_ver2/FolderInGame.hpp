#pragma once
#include "ProjectBase.hpp"

class FolderInGame
{
private:
	// プロセスが起動したかどうか
	BOOL result;		


public:
	// コンストラクタ
	FolderInGame() : result(FALSE) {}		

	// デストラクタ
	~FolderInGame() {}	


	// メイン/ exeの階層までのパスを保存した引数とexeの名前を保存した引数
	void Process(std::string createPath, std::string folderName);		


	/// ゲッター

	// 起動を確認
	bool GetbResult();		
};