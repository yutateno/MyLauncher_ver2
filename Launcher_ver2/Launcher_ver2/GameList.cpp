#include "GameList.hpp"

namespace ps = padstick;
using namespace projectbase;


void GameList::GameUpdate(int right, int left, int dicision)
{
	// �Q�[���̊m�F��ʂɈڂ�����
	if ((dicision == 1) && !createGameFlag && !gameReady)
	{
		gameReady = true;
		// ��ʃf�[�^�̎�肱��
		GetDrawScreenGraph(0, 0, 1920, 1080, drawGameReady[0]);
		GraphFilter(drawGameReady[0], DX_GRAPH_FILTER_GAUSS, 16, 1400);
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkgame));										// ������Đ�����
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
			if (!gameReadyCheck)		// �߂�I��
			{
				gameReady = false;
				gameReadyWait = 0;
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkgame));			// ������~�߂�
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);			// ����̍Đ��ʒu���ŏ��ɖ߂�
			}
			else
			{
				createGameFlag = true;																			// �Q�[���̋N���������n�߂�
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkgame));										// ������~�߂�
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);										// ����̍Đ��ʒu���ŏ��ɖ߂�
				p_folder_game->Process(p_folder_name->GetPathName(), p_folder_name->GetFolderName(now_checkgame));	// �Q�[���̋N������
			}
		}
	}

	// ��ԉE�łȂ��Ƃ��E�̃Q�[���̏ڍׂֈړ�����
	if (right == 1 && now_checkgame != gamenum && !gameReady)
	{
		now_checkgame++;													// ���̊m�F���Ă�Q�[�������ɑJ��
	}

	// ��ԍ��łȂ��Ƃ����̃Q�[���̏ڍׂֈړ�����
	if (left == 1 && now_checkgame != 0 && !gameReady)
	{
		now_checkgame--;													// ���̊m�F���Ă�Q�[������O�ɑJ��
	}
}


GameList::GameList(int defaultXSize, int defaultYSize)
{
	default_xSize = defaultXSize;
	default_ySize = defaultYSize;

	numSize = 0;
	xSize = default_xSize;
	ySize = default_ySize;


	drawWindow[SizeWindow::Default] = LoadGraph("�S���.png");
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

	gamenum = (p_folder_name->GetGameNum() - 1);		// �z��Q�ƒl�Ɏg���̂Ŏ��O��-1����

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
	// �Q�[�����N�����Ă��Ȃ��Ƃ�
	if (!createGameFlag)
	{
		if (gameReady)
		{
			// �K�E�X�t�B���^�[���{��
			DrawGraph(0, 0, drawGameReady[0], false);
			DrawExtendGraph(740, 400, 1240, 900, p_folder_media->GetMovie(now_checkgame), false);		// ����
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


			DrawFormatString(0, 0, GetColor(255, 0, 0), "%s", p_folder_media->GetText(now_checkgame).c_str());		// �e�L�X�g



			// �E�B���h�E�ύX���j���[�̃t���b�O�������Ă���Ƃ�
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
	// �Q�[�����I��������
	if (createGameFlag && !p_folder_game->GetbResult())
	{
		createGameFlag = false;
		gameReady = false;
		gameReadyCheck = false;
	}

	// ���݂̓���̍Đ����I�������
	if (gameReady && !createGameFlag && GetMovieStateToGraph(p_folder_media->GetMovie(now_checkgame)) == 0)
	{
		SeekMovieToGraph(p_folder_media->GetMovie(now_checkgame), 0);			// ����̍Đ��ʒu���ŏ��ɖ߂�
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkgame));
	}
}


void GameList::KeyProcess()
{
	// �I�v�V�������j���[���J���ĂȂ��Ƃ��̓����`���[�̑�����\��
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

	// ���R���g���[����W�L�[�ŃE�B���h�E�ύX���j���[��\���܂��͔�\���ɂ�����
	if (KeyData::Get(KEY_INPUT_Z) == 1 && !gameSelect)
	{
		windowSizeMenuFlag = true;
	}

	// �E�B���h�E�ύX���j���[�̃t���b�O�������Ă���Ƃ�
	if (windowSizeMenuFlag)
	{
		optionTextFor = 0;
		
		// ��ALT�ƃe���L�[�ŃT�C�Y��ύX���鏀��
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

		// �G���^�[�L�[�ŉ�ʃT�C�Y���w�肵�����̂ɕύX
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