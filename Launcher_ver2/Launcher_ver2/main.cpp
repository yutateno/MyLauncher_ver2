#include "GameList.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif

	int default_xSize;		// デフォルトウィンドウのXサイズ
	int default_ySize;		// デフォルトウィンドウのYサイズ
	int bitcolor;			// デフォルトウィンドウのビットカラー値

	bool endFlag = false;				// エンドコマンドを入力されたかどうか
	bool endComfirm = false;			// エンドの確認

	int fontSize = 16;			// フォントサイズ

	int colorSelect = GetColor(0, 0, 0);		// 黒

	SetWindowText("My_Launcher");	// メインウインドウのウインドウタイトルを変更する

	GetDefaultState(&default_xSize, &default_ySize, &bitcolor);		// ウィンドウデフォルト値を得る

	ChangeWindowMode(TRUE);			// ウィンドウズモードにさせるかどうか

	SetGraphMode(projectbase::WINDOW_X, projectbase::WINDOW_Y, bitcolor);					// 画像に合わせて画面サイズを変更
	SetWindowSize(default_xSize, default_ySize);		// ウィンドウサイズに合わせてゲームサイズを変更

	SetBackgroundColor(220, 220, 220);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetAlwaysRunFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	SetFontSize(fontSize);				// フォントサイズ

	SetMouseDispFlag(TRUE);			// マウスを表示

	GameList* game_list = new GameList(default_xSize, default_ySize);		// ランチャーのメイン

	// 操作
	KeyData::UpDate();
	PadData::UpDate();
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 0, 0, 0, 0, 0, 0);
	MouseData::Mouse_UpDate();
	MouseWheelData::MouseWheel_Update();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !game_list->GetLauncherEnd())
	{
		// 終了コマンドを入力してフラッグを立たせる
		if (!KeyData::CheckEnd())	// 終了はキーボードのみ
		{
			endFlag = true;
		}

		// 終了フラッグが立っていないとき
		if (!endFlag)
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
				game_list->KeyProcess();
			}
		}
		else
		{
			KeyData::UpDate();
			PadData::UpDate();
			DrawFormatString(860, 520, GetColor(255, 255, 255), "Shut Down？\nNO     YES\n		push ENTER");

			// 上の文字のNOとYESの切り替え
			if (KeyData::Get(KEY_INPUT_LEFT) == 1)
			{
				endComfirm = false;
			}
			if (KeyData::Get(KEY_INPUT_RIGHT) == 1)
			{
				endComfirm = true;
			}

			// 選択状況に応じて色を変える
			if (endComfirm)
			{
				DrawFormatString(860, 520, GetColor(255, 0, 0), "\n       YES");
			}
			else
			{
				DrawFormatString(860, 520, GetColor(255, 0, 0), "\nNO");
			}

			// エンターキーを押して選択状況に応じて
			if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
			{
				if (endComfirm)
				{
					break;
				}
				else
				{
					endFlag = false;
				}
			}
		}
	}

	delete game_list;

	DxLib::InitGraph();
	DxLib::InitSoundMem();
	DxLib::DxLib_End();

	return 0;
}