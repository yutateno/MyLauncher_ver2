#include "GameList.hpp"

namespace ps = padstick;


// ゲーム選択画面のゲームに関する描画
void GameList::DrawGameFileScroll()
{
	// ゲームの個数によってUIを変更
	if (gameNum >= 3)			// 4個以上
	{
		selectSideNum = now_checkGame / 3;			// 今何列目か確認
		

		DrawExtendGraph(192, 288, 576, 768, p_folder_media->GetDraw(3 * selectSideNum), false);					// 左


		// 真ん中に並べるゲームがあるか確認
		if (gameNum >= 3 * selectSideNum + 1)
		{
			DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(3 * selectSideNum + 1), false);		// 真ん中
		}


		// 右に並べるゲームがあるか確認
		if (gameNum >= 3 * selectSideNum + 2)
		{
			DrawExtendGraph(1344, 288, 1728, 768, p_folder_media->GetDraw(3 * selectSideNum + 2), false);		// 右
		}


		// 1列目の時
		if (selectSideNum == 0)
		{
			DrawExtendGraph(1872, 288, 2256, 768, p_folder_media->GetDraw(3 * selectSideNum + 3), false);		// 右端に4つ目のゲームをチラ見セする
		}
		// 最後の列の時
		else if (selectSideNum == gameNum / 3)
		{
			DrawExtendGraph(-336, 288, 48, 768, p_folder_media->GetDraw(3 * selectSideNum - 1), false);			// 左端に一つ前の列の最後のゲームをチラ見セする
		}
		// それ以外の時
		else
		{
			DrawExtendGraph(-336, 288, 48, 768, p_folder_media->GetDraw(3 * selectSideNum - 1), false);			// 左端に一つ前の列の最後のゲームをチラ見セする
			DrawExtendGraph(1872, 288, 2256, 768, p_folder_media->GetDraw(3 * selectSideNum + 3), false);		// 右端に4つ目のゲームをチラ見セする
		}


		// ゲームにカーソルを当てている
		if (gameSelect)
		{
			DrawBox(182 + (now_checkGame - selectSideNum * 3) * 576, 288, 586 + (now_checkGame - selectSideNum * 3) * 576, 768, 255, false);		// フォーカスを分かりやすいようにボックスで囲む
		}

	}
	else if (gameNum == 2)		// 3個以上
	{
		DrawExtendGraph(192,	288,	576,	768, p_folder_media->GetDraw(0), false);			// 左
		DrawExtendGraph(768,	288,	1152,	768, p_folder_media->GetDraw(1), false);			// 真ん中
		DrawExtendGraph(1344,	288,	1728,	768, p_folder_media->GetDraw(2), false);			// 右


		// ゲームにカーソルを当てている
		if (gameSelect)
		{
			DrawBox(182 + now_checkGame * 576, 288, 586 + now_checkGame * 576, 768, 255, false);			// フォーカスを当てて分かりやすいように
		}

	}
	else if (gameNum == 1)		// 2個以上
	{
		DrawExtendGraph(384,	288,	768,	768, p_folder_media->GetDraw(0), false);				// 左
		DrawExtendGraph(1152,	288,	1536,	768, p_folder_media->GetDraw(1), false);				// 真ん中


		// ゲームにカーソルを当てている
		if (gameSelect)
		{
			DrawBox(374 + now_checkGame * 768, 288, 778 + now_checkGame * 768, 768, 255, false);			// フォーカスを当ててやる
		}

	}
	else if (gameNum == 0)		// 1個
	{
		DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(0), false);			// ゲーム


		// ゲームにカーソルを当てている
		if (gameSelect)
		{
			DrawBox(758, 288, 1142, 768, 255, false);			// 分かりやすいように
		}
	}


	// ゲームに関するテキストを表示
	for (int i = 292; i != 1628; i += 4)
	{
		DrawLine(i, 910, i, 958, GetColor(255, 255, 255), true);		// 線を表示しまくる演出
	}	
	DrawFormatString(384, 910, GetColor(255, 0, 0), "%s", p_folder_media->GetText(now_checkGame).c_str());		// テキスト

}


// オプション画面の描画
void GameList::DrawOption()
{
	DrawGraph(1400, 10, drawLauncherEnd[0], false);				// 電源ボタン

	// ウィンドウ変更メニューのフラッグが立っているとき
	if (windowSizeMenuFlag)
	{
		// 演出用
		if (optionPerformerCount <= 40)
		{
			optionPerformerCount++;
		}


		// ウィンドウサイズを表示
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * optionPerformerCount, drawWindow[optionTextFor], false);				// ウィンドウサイズコマンド


			// 選択しているものが分かりやすいように決定コマンドの座標を移動
			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * optionPerformerCount, drawSelectWin, false);						// ウィンドウサイズを変える決定コマンド
			}

		}


		DrawGraph(1550, 10 + numSize * optionPerformerCount, drawWindow[numSize], false);						// 決定された画像を最前面にするため
	}
	else
	{
		// 演出用
		if (optionPerformerCount != 0)
		{
			optionPerformerCount--;
		}


		// ウィンドウサイズを表示
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * optionPerformerCount, drawWindow[optionTextFor], false);				// ウィンドウコマンド


			// 選択しているものが分かりやすいように決定コマンドの座標を移動
			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * optionPerformerCount, drawSelectWin, false);					// ウィンドウサイズを変える決定コマンド
			}

		}


		DrawGraph(1550, 10 + numSize * optionPerformerCount, drawWindow[numSize], false);						// 決定された画像を最前面にするため


		// ゲームにカーソルが当たっていない
		if (!gameSelect)
		{
			// カーソルが電源に当たっている
			if (!endCommandForcus)
			{
				DrawBox(1400, 10, 1440, 50, 255, false);		// フォーカス
			}
			// カーソルがウィンドウサイズに当たっている
			else
			{
				DrawBox(1500, 10, 1540, 50, 255, false);		// フォーカス
			}

		}

	}

}


// 操作に関する管理
void GameList::KeyProcess()
{
	for (int i = 0; i != PadData::GetPadNum(); ++i)
	{
		if (!endFlag)
		{
			// ゲーム選択の操作
			if (!windowSizeMenuFlag && gameSelect)
			{
				GameUpdate(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true)
					, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false), PadData::Get(XINPUT_BUTTON_A, i));
			}


			OptionKeyProcess(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_Y, i, true)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_Y, i, false), PadData::Get(XINPUT_BUTTON_A, i));
		}
		else
		{
			// ランチャーの終了の操作
			LauncherEnd(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true), PadData::Get(XINPUT_BUTTON_A, i));

		}

	}

	if (!endFlag)
	{
		// ゲーム選択の操作
		if (!windowSizeMenuFlag && gameSelect)
		{
			GameUpdate(KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_Z));
		}


		OptionKeyProcess(KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_UP), KeyData::Get(KEY_INPUT_DOWN), KeyData::Get(KEY_INPUT_Z));


		if (KeyData::Get(KEY_INPUT_ESCAPE == 1))
		{
			endFlag = true;
		}

	}
	else
	{
		// ランチャー終了の操作
		LauncherEnd(KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_Z));

	}
}


// オプション画面の操作
void GameList::OptionKeyProcess(int right, int left, int up, int down, int dicision)
{
	if (up == 1)
	{
		gameSelect = false;
	}
	if (down == 1 && !windowSizeMenuFlag)
	{
		gameSelect = true;
	}
	if (!gameSelect && !windowSizeMenuFlag)
	{
		if (right == 1)
		{
			endCommandForcus = true;
		}
		if (left == 1)
		{
			endCommandForcus = false;
		}
	}

	// 左コントロールとWキーでウィンドウ変更メニューを表示または非表示にさせる
	if (dicision == 1 && !gameSelect)
	{
		if (!endCommandForcus)
		{
			endFlag = true;
		}
		else
		{
			windowSizeMenuFlag = true;
		}
	}


	// ウィンドウ変更メニューのフラッグが立っているとき
	if (windowSizeMenuFlag)
	{
		optionTextFor = 0;
		doubleSelectWait++;
		// 左ALTとテンキーでサイズを変更する準備
		if (up == 1)
		{
			if (numSize != SizeWindow::Default)
			{
				numSize--;
			}
		}
		if (down == 1)
		{
			if (numSize != SizeWindow::Ninth)
			{
				numSize++;
			}
		}

		xSize = SizeWindow::SelectX(numSize);
		ySize = SizeWindow::SelectY(numSize);

		// エンターキーで画面サイズを指定したものに変更
		if (dicision == 1 && doubleSelectWait >= 10)
		{
			doubleSelectWait = 0;

			if (numSize == 0)
			{
				xSize = default_xSize;
				ySize = default_ySize;
			}
			SetWindowSize(xSize, ySize);

			gameSelect = true;

			windowSizeMenuFlag = false;
		}
	}
}


// ゲーム起動の操作に関する
void GameList::GameUpdate(int right, int left, int dicision)
{
	// ゲームを起動していなくてゲームの準備画面にいないときに決定コマンドを押したら
	if ((dicision == 1) && !createGameFlag && !gameReady)
	{
		gameReady = true;															// ゲームの準備画面に入ったらフラッグを立てる
		GetDrawScreenGraph(0, 0, 1920, 1080, drawGameReady[0]);						// 現在の画面をキャプチャする
		GraphFilter(drawGameReady[0], DX_GRAPH_FILTER_GAUSS, 16, 1400);				// 現在の画面にガウスフィルタかけてぼかす
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkGame));					// 動画を再生する
	}


	// ゲーム起動の準備画面
	if (gameReady)
	{
		doubleSelectWait++;


		// 右ボタンを選択するコマンドを押した
		if (right == 1)
		{
			gameReadyCheck = false;						// ゲームを起動しない方にカーソル
		}


		// 左ボタンを選択するコマンドを押した
		if (left == 1)
		{
			gameReadyCheck = true;						// ゲームを起動する方にカーソル
		}


		// 決定コマンドを押した
		if (dicision == 1 && doubleSelectWait >= 10)
		{
			// 戻るを選択
			if (!gameReadyCheck)
			{
				gameReady = false;													// ゲームの準備画面から戻る
				doubleSelectWait = 0;												// ダブルクリック防止を初期化
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkGame));			// 動画を止める
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);		// 動画の再生位置を最初に戻す
				gameReadyCheck = true;
			}
			// ゲーム起動を選択
			else
			{
				createGameFlag = true;
				doubleSelectWait = 0;																				// ダブルクリック防止を初期化
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkGame));											// 動画を止める
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);										// 動画の再生位置を最初に戻す
				p_folder_game->Process(p_folder_name->GetPathName(), p_folder_name->GetFolderName(now_checkGame));	// ゲームの起動処理
			}
		}
	}


	// 一番右でないとき右のゲームの詳細へ移動する
	if (right == 1 && now_checkGame != gameNum && !gameReady)
	{
		now_checkGame++;													// 今の確認してるゲームを次に遷移
	}


	// 一番左でないとき左のゲームの詳細へ移動する
	if (left == 1 && now_checkGame != 0 && !gameReady)
	{
		now_checkGame--;													// 今の確認してるゲームを一つ前に遷移
	}

}


// ランチャーの終了
void GameList::LauncherEnd(int left, int right, int dicision)
{
	if (endFlag)
	{
		// 上の文字のNOとYESの切り替え
		if (left == 1)
		{
			endComfirm = false;
		}
		if (right == 1)
		{
			endComfirm = true;
		}

		// エンターキーを押して選択状況に応じて
		if (dicision == 1)
		{
			if (!endComfirm)
			{
				launcher_end = true;
			}
			else
			{
				endFlag = false;
			}
		}
	}
}



// コンストラクタ
GameList::GameList(int defaultXSize, int defaultYSize)
{
	// ポインターたち
	p_folder_game = NULL;
	p_folder_name = NULL;
	p_folder_media = NULL;

	p_folder_game = new FolderInGame();
	p_folder_name = new FolderName();
	p_folder_media = new FolderInMedia(p_folder_name->GetPathName(), p_folder_name->GetGameListName()
		, p_folder_name->GetMovieListName(), p_folder_name->GetDrawListName()
		, p_folder_name->GetTextListName(), p_folder_name->GetGameNum());


	// 画像を保存する変数
	drawWindow[SizeWindow::Default]	 = LoadGraph("media\\全画面.png");
	drawWindow[SizeWindow::First]	 = LoadGraph("media\\640x480.png");
	drawWindow[SizeWindow::Second]	 = LoadGraph("media\\768x576.png");
	drawWindow[SizeWindow::Third]	 = LoadGraph("media\\1024x768.png");
	drawWindow[SizeWindow::Fourth]	 = LoadGraph("media\\1280x720.png");
	drawWindow[SizeWindow::Fifth]	 = LoadGraph("media\\1366x768.png");
	drawWindow[SizeWindow::Sixth]	 = LoadGraph("media\\1920x1080.png");
	drawWindow[SizeWindow::Seventh]	 = LoadGraph("media\\2048x1536.png");
	drawWindow[SizeWindow::Eighth]	 = LoadGraph("media\\2560x1440.png");
	drawWindow[SizeWindow::Ninth]	 = LoadGraph("media\\3200x2400.png");

	drawSelectWin = LoadGraph("media\\windowselect.png");

	drawGameReady[0] = MakeScreen(1920, 1080);
	drawGameReady[1] = LoadGraph("media\\gamestart.png");
	drawGameReady[2] = LoadGraph("media\\start.png");
	drawGameReady[3] = LoadGraph("media\\back.png");

	drawLauncherEnd[0] = LoadGraph("media\\dengen.png");
	drawLauncherEnd[1] = LoadGraph("media\\終了確認.png");
	drawLauncherEnd[2] = LoadGraph("media\\endtrue.png");
	drawLauncherEnd[3] = drawGameReady[3];


	// ゲーム一覧に関する
	gameNum = (p_folder_name->GetGameNum() - 1);		// 配列参照値に使うので事前に-1する
	now_checkGame = 0;
	selectSideNum = 0;


	// ゲームの起動に関する
	gameReady = false;
	gameReadyCheck = true;
	createGameFlag = false;


	// ランチャー終了に関する
	launcher_end = false;
	endFlag = false;
	endComfirm = false;
	endCommandForcus = false;
	if (gameNum == -1)
	{
		forceEnd = true;
	}
	else
	{
		forceEnd = false;
	}
	forceEndCount = 0;


	// ウィンドウサイズ変更に関する
	default_xSize = defaultXSize;
	default_ySize = defaultYSize;
	numSize = 0;
	xSize = default_xSize;
	ySize = default_ySize;
	gameSelect = true;
	windowSizeMenuFlag = false;
	optionTextFor = 0;
	optionPerformerCount = 0;


	// 操作に関する
	doubleSelectWait = 0;
}


GameList::~GameList()
{
	POINTER_RELEASE(p_folder_name);
	POINTER_RELEASE(p_folder_game);
	POINTER_RELEASE(p_folder_media);

	for (int i = 0; i != 4; ++i)
	{
		GRAPHIC_RELEASE(drawLauncherEnd[i]);
	}
	for (int i = 0; i != 4; ++i)
	{
		GRAPHIC_RELEASE(drawGameReady[i]);
	}
	GRAPHIC_RELEASE(drawSelectWin);
	for (int i = 0; i != 10; ++i)
	{
		GRAPHIC_RELEASE(drawWindow[i]);
	}
}


void GameList::Draw()
{
	if (forceEnd)
	{
		DrawFormatString(500, 500, GetColor(0, 0, 0), "ゲームファイルが存在しません。数秒後強制終了します。\nDon't Game Folder. Force Quit An Application.");
	}
	else
	{
		// ゲームを起動していないとき
		if (!createGameFlag && !endFlag)
		{
			if (gameReady)
			{
				DrawGraph(0, 0, drawGameReady[0], false);			// ガウスフィルターを施した画像
				DrawExtendGraph(384, 96, 1536, 768, p_folder_media->GetMovie(now_checkGame), false);		// 動画
				DrawFormatString(400, 48, 255, "%s", p_folder_name->GetGameListName()[now_checkGame].c_str());
				DrawGraph(768, 864, drawGameReady[1], false);
				DrawGraph(480, 960, drawGameReady[2], false);
				DrawGraph(1056, 960, drawGameReady[3], false);
				if (gameReadyCheck)
				{
					DrawBox(480, 960, 813, 1023, 255, false);
				}
				else
				{
					DrawBox(1056, 960, 1389, 1023, 255, false);
				}
			}
			else
			{
				DrawGameFileScroll();

				DrawOption();			// ウィンドウオプション
			}
		}

		if (endFlag)
		{
			DrawGraph(700, 520, drawLauncherEnd[1], false);
			DrawGraph(500, 720, drawLauncherEnd[2], false);
			DrawGraph(900, 720, drawLauncherEnd[3], false);
			// 選択状況に応じて色を変える
			if (!endComfirm)
			{
				DrawBox(500, 720, 833, 783, 255, false);
			}
			else
			{
				DrawBox(900, 720, 1233, 783, 255, false);
			}
		}
	}
#ifdef DEBUG_PRINTFDX
	printfDx("%d\n", forceEndCount);
#endif // DEBUG_PRINTFDX
}


void GameList::Process()
{
	if (forceEnd)
	{
		forceEndCount++;
		if (forceEndCount >= 300)
		{
			launcher_end = true;
		}
	}
	else
	{
		if (!createGameFlag)
		{
			KeyProcess();
		}

		// ゲームが終了したら
		if (createGameFlag && !p_folder_game->GetbResult())
		{
			createGameFlag = false;
			gameReady = false;
		}

		// 現在の動画の再生が終わったら
		if (gameReady && !createGameFlag && GetMovieStateToGraph(p_folder_media->GetMovie(now_checkGame)) == 0)
		{
			SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);			// 動画の再生位置を最初に戻す
			PlayMovieToGraph(p_folder_media->GetMovie(now_checkGame));
		}
	}
}


bool GameList::GetCreateGame()
{
	return createGameFlag;
}


bool GameList::GetLauncherEnd()
{
	return launcher_end;
}
