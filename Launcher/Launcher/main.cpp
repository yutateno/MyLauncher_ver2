#include "GameList.h"

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

	bool optionMenuFlag = false;		// オプションメニューの表示フラッグ
	bool windowSizeMenuFlag = false;	// ウィンドウサイズ変更メニューの表示フラッグ

	bool endFlag = false;				// エンドコマンドを入力されたかどうか
	bool endComfirm = false;			// エンドの確認

	int fontSize = 16;			// フォントサイズ

	int optionTextFor = 0;		// forループ数値のためのもの
	int colorSelect = projectbase::COLOR_BLOCK;		// 黒

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

	SetWindowText("My_Launcher");	// メインウインドウのウインドウタイトルを変更する

	GetDefaultState(&default_xSize, &default_ySize, &bitcolor);		// ウィンドウデフォルト値を得る

	int numSize = 0;
	int xSize = default_xSize;			// サイズ変更後のXサイズ
	int ySize = default_ySize;			// サイズ変更後のYサイズ

	ChangeWindowMode(TRUE);			// ウィンドウズモードにさせるかどうか

	SetGraphMode(projectbase::WINDOW_X, projectbase::WINDOW_Y, bitcolor);					// 画像に合わせて画面サイズを変更
	SetWindowSize(default_xSize, default_ySize);		// ウィンドウサイズに合わせてゲームサイズを変更

	if(DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetAlwaysRunFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	SetFontSize(fontSize);				// フォントサイズ

	SetMouseDispFlag(TRUE);			// マウスを表示

	GameList* game_list = new GameList();		// ランチャーのメイン

	// 操作
	KeyData::UpDate();
	PadData::UpDate();
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 0, 0, 0, 0, 0, 0);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 &&!game_list->GetLauncherEnd())
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

			// オプションメニューが表示していないとき
			if (!optionMenuFlag)
			{
				game_list->Process();		// ここのみランチャー内の動作
			}

			// ゲームが起動していないとき
			if (!game_list->GetCreateGame())
			{
				KeyData::UpDate();
				PadData::UpDate();
				// オプションメニューを開いてないときはランチャーの操作を可能に
				if (!optionMenuFlag && !windowSizeMenuFlag)
				{
					game_list->KeyProcess();
				}
			}

			// 左コントロールとQキーでオプションメニューを表示または非表示にさせる
			if (KeyData::Get(KEY_INPUT_LCONTROL) >= 1 && KeyData::Get(KEY_INPUT_Q) == 1 && !windowSizeMenuFlag)
			{
				optionMenuFlag = !optionMenuFlag;
			}

			// オプションメニューのフラッグが立っているとき
			if (optionMenuFlag)
			{
				DrawBox(0, 0, 400, 120, projectbase::COLOR_SKY_BLUE, true);		// 水色にしたかったからした
				DrawFormatString(5, 5, projectbase::COLOR_BLOCK, "Option Key\n\nWindowSizeChange : LeftCtrl & W\nSoundStart : LeftCtrl & S\n\nClose : Left Ctrl & Q");
			}

			// 左コントロールとWキーでウィンドウ変更メニューを表示または非表示にさせる
			if (KeyData::Get(KEY_INPUT_LCONTROL) >= 1 && KeyData::Get(KEY_INPUT_W) == 1)
			{
				optionMenuFlag = false;
				windowSizeMenuFlag = !windowSizeMenuFlag;
			}

			// ウィンドウ変更メニューのフラッグが立っているとき
			if (windowSizeMenuFlag)
			{
				DrawBox(0, 0, 200, 275, projectbase::COLOR_SKY_BLUE, true);		// 水色にしたかったからした

				optionTextFor = 0;
				DrawFormatString(5, 3 + optionTextFor * fontSize, GetColor(0, 0, 0), "WindowSizeChange\n\nALT+");

				if (numSize == optionTextFor)
				{
					colorSelect = projectbase::COLOR_RED;
				}
				DrawFormatString(5, 5 + (optionTextFor + 3) * fontSize, colorSelect, "0 : Reset");
				if (colorSelect == projectbase::COLOR_RED)	// for内で一回しか通らないからelseではなくこうする
				{
					colorSelect = projectbase::COLOR_BLOCK;
				}

				for (optionTextFor = SizeWindow::Select::First; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
				{
					if (numSize == optionTextFor)
					{
						colorSelect = projectbase::COLOR_RED;
					}
					DrawFormatString(5, 5 + (optionTextFor + 3) * fontSize, colorSelect, "%d : %dx%d"
						, optionTextFor, SizeWindow::SelectX(optionTextFor), SizeWindow::SelectY(optionTextFor));
					if (colorSelect == projectbase::COLOR_RED)	// for内で一回しか通らないからelseではなくこうする
					{
						colorSelect = projectbase::COLOR_BLOCK;
					}
				}

				DrawFormatString(5, 5 + (optionTextFor + 3) * fontSize, GetColor(0, 0, 0), "		after push ENTER\n\nClose : Left Ctrl & W");

				// 左ALTとテンキーでサイズを変更する準備
				if (KeyData::Get(KEY_INPUT_LALT) >= 1)
				{
					if (KeyData::Get(KEY_INPUT_1) == 1)
					{
						numSize = SizeWindow::First;
					}
					if (KeyData::Get(KEY_INPUT_2) == 1)
					{
						numSize = SizeWindow::Second;
					}
					if (KeyData::Get(KEY_INPUT_3) == 1)
					{
						numSize = SizeWindow::Third;
					}
					if (KeyData::Get(KEY_INPUT_4) == 1)
					{
						numSize = SizeWindow::Fourth;
					}
					if (KeyData::Get(KEY_INPUT_5) == 1)
					{
						numSize = SizeWindow::Fifth;
					}
					if (KeyData::Get(KEY_INPUT_6) == 1)
					{
						numSize = SizeWindow::Sixth;
					}
					if (KeyData::Get(KEY_INPUT_7) == 1)
					{
						numSize = SizeWindow::Seventh;
					}
					if (KeyData::Get(KEY_INPUT_8) == 1)
					{
						numSize = SizeWindow::Eighth;
					}
					if (KeyData::Get(KEY_INPUT_9) == 1)
					{
						numSize = SizeWindow::Ninth;
					}
					if (KeyData::Get(KEY_INPUT_0) == 1)
					{
						numSize = SizeWindow::Default;
					}
					xSize = SizeWindow::SelectX(numSize);
					ySize = SizeWindow::SelectY(numSize);
				}

				// エンターキーで画面サイズを指定したものに変更
				if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
				{
					if (numSize == 0)
					{
						xSize = default_xSize;
						ySize = default_ySize;
					}
					SetWindowSize(xSize, ySize);
				}
			}
		}
		else
		{
			KeyData::UpDate();
			PadData::UpDate();
			DrawFormatString(860, 520, projectbase::COLOR_WHITE, "Shut Down？\nNO     YES\n		push ENTER");

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
				DrawFormatString(860, 520, projectbase::COLOR_RED, "\n       YES");
			}
			else
			{
				DrawFormatString(860, 520, projectbase::COLOR_RED, "\nNO");
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