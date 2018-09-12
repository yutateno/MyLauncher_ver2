#include "GameList.hpp"

namespace ps = padstick;
using namespace projectbase;


void GameList::GameUpdate(int right, int left, int dicision)
{
	// ゲームの確認画面に移ったら
	if ((dicision == 1) && !createGameFlag && !gameReady)
	{
		gameReady = true;
		// 画面データの取りこみ
		GetDrawScreenGraph(0, 0, 1920, 1080, drawGameReady[0]);
		GraphFilter(drawGameReady[0], DX_GRAPH_FILTER_GAUSS, 16, 1400);
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkgame));										// 動画を再生する
	}
	if (gameReady)
	{
		gameReadyWait++;
		if (right == 1)
		{
			gameReadyCheck = false;
		}
		if (left == 1)
		{
			gameReadyCheck = true;
		}

		if (dicision == 1 && gameReadyWait >= 10)
		{
			if (!gameReadyCheck)		// 戻る選択
			{
				gameReady = false;
				gameReadyWait = 0;
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkgame));			// 動画を止める
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
			}
			else
			{
				createGameFlag = true;																			// ゲームの起動処理を始める
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkgame));										// 動画を止める
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);										// 動画の再生位置を最初に戻す
				p_folder_game->Process(p_folder_name->GetPathName(), p_folder_name->GetFolderName(now_checkgame));	// ゲームの起動処理
			}
		}
	}

	// 一番右でないとき右のゲームの詳細へ移動する
	if (right == 1 && now_checkgame != gamenum && !gameReady)
	{
		now_checkgame++;													// 今の確認してるゲームを次に遷移
	}

	// 一番左でないとき左のゲームの詳細へ移動する
	if (left == 1 && now_checkgame != 0 && !gameReady)
	{
		now_checkgame--;													// 今の確認してるゲームを一つ前に遷移
	}
}


GameList::GameList(int defaultXSize, int defaultYSize)
{
	default_xSize = defaultXSize;
	default_ySize = defaultYSize;

	numSize = 0;
	xSize = default_xSize;
	ySize = default_ySize;


	drawWindow[SizeWindow::Default] = LoadGraph("全画面.png");
	drawWindow[SizeWindow::First] = LoadGraph("640x480.png");
	drawWindow[SizeWindow::Second] = LoadGraph("768x576.png");
	drawWindow[SizeWindow::Third] = LoadGraph("1024x768.png");
	drawWindow[SizeWindow::Fourth] = LoadGraph("1280x720.png");
	drawWindow[SizeWindow::Fifth] = LoadGraph("1366x768.png");
	drawWindow[SizeWindow::Sixth] = LoadGraph("1920x1080.png");
	drawWindow[SizeWindow::Seventh] = LoadGraph("2048x1536.png");
	drawWindow[SizeWindow::Eighth] = LoadGraph("2560x1440.png");
	drawWindow[SizeWindow::Ninth] = LoadGraph("3200x2400.png");

	drawSelectWin = LoadGraph("windowselect.png");

	drawGameReady[0] = MakeScreen(1920, 1080);
	drawGameReady[1] = LoadGraph("gamestart.png");
	drawGameReady[2] = LoadGraph("start.png");
	drawGameReady[3] = LoadGraph("back.png");

	gameSelect = true;

	windowSizeMenuFlag = false;

	launcher_end = false;

	optionTextFor = 0;

	p_folder_game = NULL;
	p_folder_name = NULL;
	p_folder_media = NULL;

	p_folder_game = new FolderInGame();

	p_folder_name = new FolderName();

	p_folder_media = new FolderInMedia(p_folder_name->GetPathName(), p_folder_name->GetGameListName()
		, p_folder_name->GetMovieListName(), p_folder_name->GetDrawListName(), p_folder_name->GetTextListName(), p_folder_name->GetGameNum());

	createGameFlag = false;

	gameReadyCheck = false;

	gameReady = false;

	gameReadyWait = 0;

	gamenum = (p_folder_name->GetGameNum() - 1);		// 配列参照値に使うので事前に-1する

	now_checkgame = 0;
}


GameList::~GameList()
{
	if (p_folder_name != NULL)
	{
		delete p_folder_name;
	}
	if (p_folder_game != NULL)
	{
		delete p_folder_game;
	}
	if (p_folder_media != NULL)
	{
		delete p_folder_media;
	}
	for (int i = 0; i != 4; ++i)
	{
		DeleteGraph(drawGameReady[i]);
	}
	DeleteGraph(drawSelectWin);
	for (int i = 0; i != 10; ++i)
	{
		DeleteGraph(drawWindow[i]);
	}
}


void GameList::Draw()
{
	// ゲームを起動していないとき
	if (!createGameFlag)
	{
		if (gameReady)
		{
			// ガウスフィルターを施す
			DrawGraph(0, 0, drawGameReady[0], false);
			DrawExtendGraph(740, 400, 1240, 900, p_folder_media->GetMovie(now_checkgame), false);		// 動画
			DrawGraph(500, 930, drawGameReady[1], false);
			DrawGraph(300, 970, drawGameReady[2], false);
			DrawGraph(900, 970, drawGameReady[3], false);
			if (gameReadyCheck)
			{
				DrawBox(290, 960, 630, 1030, 255, false);
			}
			else
			{
				DrawBox(890, 960, 1230, 1030, 255, false);
			}
		}
		else
		{
			DrawExtendGraph(540, 400, 1040, 900, p_folder_media->GetDraw(now_checkgame), false);


			DrawFormatString(0, 0, GetColor(255, 0, 0), "%s", p_folder_media->GetText(now_checkgame).c_str());		// テキスト



			// ウィンドウ変更メニューのフラッグが立っているとき
			if (windowSizeMenuFlag)
			{
				for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
				{
					DrawGraph(1550, 10 + optionTextFor * 40, drawWindow[optionTextFor], false);

					if (numSize == optionTextFor)
					{
						DrawGraph(1500, 10 + optionTextFor * 40, drawSelectWin, false);
					}
				}
			}
			else
			{
				DrawGraph(1550, 10, drawWindow[numSize], false);

				DrawGraph(1500, 10, drawSelectWin, false);

				if (gameSelect)
				{
					DrawBox(530, 390, 1050, 910, 255, false);
				}
				else
				{
					DrawBox(1500, 10, 1540, 40, 255, false);
				}
			}
		}
	}
}


void GameList::Process()
{
	// ゲームが終了したら
	if (createGameFlag && !p_folder_game->GetbResult())
	{
		createGameFlag = false;
		gameReady = false;
		gameReadyCheck = false;
	}

	// 現在の動画の再生が終わったら
	if (gameReady && !createGameFlag && GetMovieStateToGraph(p_folder_media->GetMovie(now_checkgame)) == 0)
	{
		SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkgame));
	}
}


void GameList::KeyProcess()
{
	// オプションメニューを開いてないときはランチャーの操作を可能に
	if (!windowSizeMenuFlag && gameSelect)
	{
		for (int i = 0; i != PadData::GetPadNum(); ++i)
		{
			GameUpdate(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false), PadData::Get(XINPUT_BUTTON_A, i));
		}

		GameUpdate(KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_SPACE));
	}

	if (KeyData::Get(KEY_INPUT_UP) == 1)
	{
		if (gameSelect)
		{
			gameSelect = false;
		}
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1)
	{
		if (!gameSelect)
		{
			gameSelect = true;
		}
	}

	// 左コントロールとWキーでウィンドウ変更メニューを表示または非表示にさせる
	if (KeyData::Get(KEY_INPUT_Z) == 1 && !gameSelect)
	{
		windowSizeMenuFlag = true;
	}

	// ウィンドウ変更メニューのフラッグが立っているとき
	if (windowSizeMenuFlag)
	{
		optionTextFor = 0;
		
		// 左ALTとテンキーでサイズを変更する準備
		if (KeyData::Get(KEY_INPUT_UP) == 1)
		{
			if (numSize != SizeWindow::Default)
			{
				numSize--;
			}
		}
		if (KeyData::Get(KEY_INPUT_DOWN) == 1)
		{
			if (numSize != SizeWindow::Ninth)
			{
				numSize++;
			}
		}

		xSize = SizeWindow::SelectX(numSize);
		ySize = SizeWindow::SelectY(numSize);

		// エンターキーで画面サイズを指定したものに変更
		if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
		{
			if (numSize == 0)
			{
				xSize = default_xSize;
				ySize = default_ySize;
			}
			SetWindowSize(xSize, ySize);

			windowSizeMenuFlag = false;
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