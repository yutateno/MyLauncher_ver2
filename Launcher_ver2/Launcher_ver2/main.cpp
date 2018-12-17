#include "GameList.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif

	int default_xSize = 1920;		// デフォルトウィンドウのXサイズ
	int default_ySize = 1080;		// デフォルトウィンドウのYサイズ
	int bitcolor = 32;				// デフォルトウィンドウのビットカラー値


	int fontSize = 48;			// フォントサイズ


	SetWindowText("My_Launcher");	// メインウインドウのウインドウタイトルを変更する


	GetDefaultState(&default_xSize, &default_ySize, &bitcolor);		// ウィンドウデフォルト値を得る


	ChangeWindowMode(TRUE);			// ウィンドウズモードにさせるかどうか


	SetGraphMode(1920, 1080, bitcolor);					// 画像に合わせて画面サイズを変更
	SetWindowSize(default_xSize, default_ySize);		// ウィンドウサイズに合わせてゲームサイズを変更


	SetBackgroundColor(230, 230, 230);			// 背景色


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}


	SetAlwaysRunFlag(TRUE);					// 裏画面でも動作


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画


	SetFontSize(fontSize);				// フォントサイズ


	SetMouseDispFlag(TRUE);			// マウスを表示


	GameList* game_list = NULL;
	game_list = new GameList(default_xSize, default_ySize);		// ランチャーのメイン


	// 操作
	KeyData::UpDate();
	PadData::UpDate();
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 0, 0, 0, 0, 0, 0);
	MouseData::Mouse_UpDate();
	MouseWheelData::MouseWheel_Update();


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !game_list->GetLauncherEnd())
	{
		game_list->Draw();		// ここのみ描画


		game_list->Process();		// ランチャー内の動作


		// ゲームが起動していないとき
		if (!game_list->GetCreateGame())
		{
			KeyData::UpDate();
			PadData::UpDate();
			MouseData::Mouse_UpDate();
			MouseWheelData::MouseWheel_Update();
		}
	}


	POINTER_RELEASE(game_list);


	InitGraph();
	InitSoundMem();
	DxLib_End();


	return 0;
}