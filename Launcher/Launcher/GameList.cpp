#include "GameList.h"

namespace ps = padstick;
using namespace projectbase;

void GameList::KeyAtach(int right, int left, int dicision)
{
	// ゲームを起動していないときにスペースボタンを押したら
	if ((dicision == 1) && !createGameFlag && !gameReady)
	{
		gameReady = true;
		PauseMovieToGraph(folder_media->GetMovie(now_checkgame));										// 動画を止める
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
			if (!gameReadyCheck)
			{
				gameReady = false;
				gameReadyWait = 0;
				PlayMovieToGraph(folder_media->GetMovie(now_checkgame));										// 動画を再生する
			}
			else
			{
				// BGMを再生してるとき
				if (CheckSoundMem(s_bgm))
				{
					StopSoundMem(s_bgm);	// BGMを止める
				}

				createGameFlag = true;																			// ゲームの起動処理を始める
				SeekMovieToGraph(folder_media->GetMovie(now_checkgame), 0);										// 動画の再生位置を最初に戻す
				folder_game->Process(folder_name->GetPathName(), folder_name->GetFolderName(now_checkgame));	// ゲームの起動処理
																												// ゲームが終了した
				SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));					// 動画の音量を通常に
				PlayMovieToGraph(folder_media->GetMovie(now_checkgame));										// 動画を再生する
			}
		}
	}

	// 一番右でないとき右のゲームの詳細へ移動する
	if (right == 1 && now_checkgame != gamenum && !gameReady)
	{
		PauseMovieToGraph(folder_media->GetMovie(now_checkgame));			// 動画を止める
		SeekMovieToGraph(folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
		now_checkgame++;													// 今の確認してるゲームを次に遷移

																			// BGMを再生していないとき
		if (!CheckSoundMem(s_bgm))
		{
			SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));		// 動画の音量を通常に
		}
		else
		{
			SetMovieVolumeToGraph(0, folder_media->GetMovie(now_checkgame));					// 動画の音量を消す
		}

		PlayMovieToGraph(folder_media->GetMovie(now_checkgame));		// 動画を再生する
	}

	// 一番左でないとき左のゲームの詳細へ移動する
	if (left == 1 && now_checkgame != 0 && !gameReady)
	{
		PauseMovieToGraph(folder_media->GetMovie(now_checkgame));			// 動画を止める
		SeekMovieToGraph(folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
		now_checkgame--;													// 今の確認してるゲームを一つ前に遷移

																			// BGMを再生していないとき
		if (!CheckSoundMem(s_bgm))
		{
			SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));		// 動画の音量を通常に
		}
		else
		{
			SetMovieVolumeToGraph(0, folder_media->GetMovie(now_checkgame));					// 動画の音量を消す
		}

		PlayMovieToGraph(folder_media->GetMovie(now_checkgame));		// 動画を再生する
	}
}

GameList::GameList()
{
	launcher_end = false;

	folder_game = new FolderInGame();

	folder_name = new FolderName();

	folder_media = new FolderInMedia(folder_name->GetPathName(), folder_name->GetGameListName()
		, folder_name->GetMovieListName(), folder_name->GetDrawListName(), folder_name->GetTextListName(), folder_name->GetGameNum());

	createGameFlag = false;

	fontData = CreateFontToHandle(NULL, CHANGE_FONT_DATA_SIZE, 3, -1);

	gameReadyCheck = false;

	gameReady = false;

	gameReadyWait = 0;

	s_bgm = LoadSoundMem("bgm.wav");

	gamenum = (folder_name->GetGameNum() - 1);		// 配列参照値に使うので事前に-1する

	now_checkgame = 0;

	moviecount = 0;

	PlayMovieToGraph(folder_media->GetMovie(now_checkgame));	// 動画を再生始める
}

GameList::~GameList()
{
	delete folder_name;
	delete folder_game;
	delete folder_media;

	DeleteSoundMem(s_bgm);
}

void GameList::Draw()
{
	// ゲームを起動していないとき
	if (!createGameFlag)
	{
		DrawGraph(0, 0, folder_media->GetDraw(now_checkgame)[0], true);	// 背景

		// タイトルロゴ
		if (gamenum == 0)
		{
			DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
				TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
		}
		else if (gamenum == 1)
		{
			if (now_checkgame == 0)
			{
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
			}
			else
			{
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
			}
		}
		else if (gamenum == 2 || gamenum == 3)
		{
			if (now_checkgame == 0)
			{
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
			}
			else if (now_checkgame <= gamenum - 1)
			{
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
			}
			else
			{
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
			}
		}
		else
		{
			if (now_checkgame == 0)
			{
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_SECOND_RIGHT_CENTER_X - TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y - TITLE_DRAW_SECOND_RIGHT_Y,
					TITLE_DRAW_SECOND_RIGHT_CENTER_X + TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y + TITLE_DRAW_SECOND_RIGHT_Y, folder_media->GetDraw(now_checkgame + 2)[1], true);
			}
			else if (now_checkgame == 1)
			{
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_SECOND_RIGHT_CENTER_X - TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y - TITLE_DRAW_SECOND_RIGHT_Y,
					TITLE_DRAW_SECOND_RIGHT_CENTER_X + TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y + TITLE_DRAW_SECOND_RIGHT_Y, folder_media->GetDraw(now_checkgame + 2)[1], true);
			}
			else if (now_checkgame >= 2 && now_checkgame <= gamenum - 2)
			{
				DrawExtendGraph(TITLE_DRAW_SECOND_LEFT_CENTER_X - TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y - TITLE_DRAW_SECOND_LEFT_Y,
					TITLE_DRAW_SECOND_LEFT_CENTER_X + TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y + TITLE_DRAW_SECOND_LEFT_Y, folder_media->GetDraw(now_checkgame - 2)[1], true);
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_SECOND_RIGHT_CENTER_X - TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y - TITLE_DRAW_SECOND_RIGHT_Y,
					TITLE_DRAW_SECOND_RIGHT_CENTER_X + TITLE_DRAW_SECOND_RIGHT_X, TITLE_DRAW_SECOND_RIGHT_CENTER_Y + TITLE_DRAW_SECOND_RIGHT_Y, folder_media->GetDraw(now_checkgame + 2)[1], true);
			}
			else if (now_checkgame == gamenum - 1)
			{
				DrawExtendGraph(TITLE_DRAW_SECOND_LEFT_CENTER_X - TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y - TITLE_DRAW_SECOND_LEFT_Y,
					TITLE_DRAW_SECOND_LEFT_CENTER_X + TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y + TITLE_DRAW_SECOND_LEFT_Y, folder_media->GetDraw(now_checkgame - 2)[1], true);
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
				DrawExtendGraph(TITLE_DRAW_RIGHT_CENTER_X - TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y - TITLE_DRAW_RIGHT_Y,
					TITLE_DRAW_RIGHT_CENTER_X + TITLE_DRAW_RIGHT_X, TITLE_DRAW_RIGHT_CENTER_Y + TITLE_DRAW_RIGHT_Y, folder_media->GetDraw(now_checkgame + 1)[1], true);
			}
			else
			{
				DrawExtendGraph(TITLE_DRAW_SECOND_LEFT_CENTER_X - TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y - TITLE_DRAW_SECOND_LEFT_Y,
					TITLE_DRAW_SECOND_LEFT_CENTER_X + TITLE_DRAW_SECOND_LEFT_X, TITLE_DRAW_SECOND_LEFT_CENTER_Y + TITLE_DRAW_SECOND_LEFT_Y, folder_media->GetDraw(now_checkgame - 2)[1], true);
				DrawExtendGraph(TITLE_DRAW_LEFT_CENTER_X - TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y - TITLE_DRAW_LEFT_Y,
					TITLE_DRAW_LEFT_CENTER_X + TITLE_DRAW_LEFT_X, TITLE_DRAW_LEFT_CENTER_Y + TITLE_DRAW_LEFT_Y, folder_media->GetDraw(now_checkgame - 1)[1], true);
				DrawExtendGraph(TITLE_DRAW_CENTER_CENTER_X - TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y - TITLE_DRAW_CIRCLE_Y,
					TITLE_DRAW_CENTER_CENTER_X + TITLE_DRAW_CIRCLE_X, TITLE_DRAW_CENTER_CENTER_Y + TITLE_DRAW_CIRCLE_Y, folder_media->GetDraw(now_checkgame)[1], true);
			}
		}

		DrawExtendGraph(MOVIE_CENTER_X - MOVIE_LONG_X, MOVIE_CENTER_Y - MOVIE_LONG_Y,
			MOVIE_CENTER_X + MOVIE_LONG_X - 1, MOVIE_CENTER_Y + MOVIE_LONG_Y - 1, folder_media->GetMovie(now_checkgame), false);		// 動画

		DrawGraph(TEXT_BOX_FIRST_X, TEXT_BOX_FIRST_Y, folder_media->GetDraw(now_checkgame)[2], true);		// テキストのボックス背景
		for (int i = 0; i != folder_media->GetText(now_checkgame).size(); ++i)
		{
			DrawFormatString(TEXT_X, TEXT_Y + i * TEXT_SPACE, COLOR_WHITE, "%s", folder_media->GetText(now_checkgame)[i].c_str());		// テキスト
		}

		if (gameReady)
		{
			DrawGraph(DRAW_GAMECHECK_AREA_X, DRAW_GAMECHECK_AREA_Y, folder_media->GetDraw(now_checkgame)[3], true);
			DrawFormatStringToHandle(DRAW_GAMECHECK_AREA_X + DRAW_GAMECHECK_TEXTAREA_X, DRAW_GAMECHECK_AREA_Y + DRAW_GAMECHECK_TEXTAREA_Y, COLOR_BLOCK, fontData, "「%s」\nを起動しますか？\n   YES ・ NO", folder_name->GetFolderName(now_checkgame).c_str());
			if (gameReadyCheck)
			{
				DrawStringToHandle(DRAW_GAMECHECK_AREA_X + DRAW_GAMECHECK_TEXTAREA_X, DRAW_GAMECHECK_AREA_Y + DRAW_GAMECHECK_TEXTAREA_Y, "\n\n   YES", COLOR_RED, fontData);
			}
			else
			{
				DrawStringToHandle(DRAW_GAMECHECK_AREA_X + DRAW_GAMECHECK_TEXTAREA_X, DRAW_GAMECHECK_AREA_Y + DRAW_GAMECHECK_TEXTAREA_Y, "\n\n          NO", COLOR_RED, fontData);
			}
		}
	}
}

void GameList::Process()
{
	// ゲームが終了したら
	if (createGameFlag&& !folder_game->GetbResult())
	{
		createGameFlag = false;
		gameReady = false;
		gameReadyCheck = false;
	}

	// 現在の動画の再生が終わったら
	if (!gameReady && !createGameFlag && GetMovieStateToGraph(folder_media->GetMovie(now_checkgame)) == 0)
	{
		moviecount++;
		if (moviecount >= MOVIE_MOVE_FLAME)
		{
			// 一番右ではないとき
			if (now_checkgame != gamenum)
			{
				SeekMovieToGraph(folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
				now_checkgame++;
				SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));
				PlayMovieToGraph(folder_media->GetMovie(now_checkgame));
			}
			else
			{
				SeekMovieToGraph(folder_media->GetMovie(now_checkgame), 0);			// 動画の再生位置を最初に戻す
				now_checkgame = 0;
				SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));
				PlayMovieToGraph(folder_media->GetMovie(now_checkgame));
			}
			moviecount = 0;
		}
	}
}

void GameList::KeyProcess()
{
	for (int i = 0; i != PadData::GetPadNum(); ++i)
	{
		KeyAtach(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true)
			, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false), PadData::Get(XINPUT_BUTTON_A, i));
	}

	KeyAtach(KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_SPACE));

	// 左コントロールとSキーでBGMを再生する
	if (KeyData::Get(KEY_INPUT_LCONTROL) >= 1 && KeyData::Get(KEY_INPUT_S) == 1)
	{
		// BGMを再生していないとき
		if (!CheckSoundMem(s_bgm))
		{
			SetMovieVolumeToGraph(0, folder_media->GetMovie(now_checkgame));	// 動画の音量を消す
			PlaySoundMem(s_bgm, DX_PLAYTYPE_LOOP, true);						// BGMを再生する
#ifdef _DEBUG
			ChangeVolumeSoundMem(125, s_bgm);
#endif
		}
		else
		{
			StopSoundMem(s_bgm);																// BGMを止める
			SetMovieVolumeToGraph(MOVEI_VOLUME_MAX, folder_media->GetMovie(now_checkgame));		// 動画の音量を通常に
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