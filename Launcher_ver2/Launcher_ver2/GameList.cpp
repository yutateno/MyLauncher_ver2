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


void GameList::DrawGameFileScroll()
{
	if (gamenum >= 3)			// 4�ȏ�
	{
		selectSideNum = now_checkgame / 3;
		
		DrawExtendGraph(192, 288, 576, 768, p_folder_media->GetDraw(3 * selectSideNum), false);

		if (gamenum >= 3 * selectSideNum + 1)
		{
			DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(3 * selectSideNum + 1), false);
		}
		if (gamenum >= 3 * selectSideNum + 2)
		{
			DrawExtendGraph(1344, 288, 1728, 768, p_folder_media->GetDraw(3 * selectSideNum + 2), false);
		}

		if (selectSideNum == 0)
		{
			DrawExtendGraph(1872, 288, 2256, 768, p_folder_media->GetDraw(3 * selectSideNum + 3), false);
		}
		else if (scrollNum == selectSideNum)
		{
			DrawExtendGraph(-336, 288, 48, 768, p_folder_media->GetDraw(3 * selectSideNum - 1), false);
		}

		if (gameSelect)
		{
			DrawBox(182 + (now_checkgame - selectSideNum * 3) * 576, 288, 586 + (now_checkgame - selectSideNum * 3) * 576, 768, 255, false);
		}
	}
	else if (gamenum == 2)		// 3�ȏ�
	{
		DrawExtendGraph(192, 288, 576, 768, p_folder_media->GetDraw(0), false);

		DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(1), false);

		DrawExtendGraph(1344, 288, 1728, 768, p_folder_media->GetDraw(2), false);

		if (gameSelect)
		{
			DrawBox(182 + now_checkgame * 576, 288, 586 + now_checkgame * 576, 768, 255, false);
		}
	}
	else if (gamenum == 1)		// 2�ȏ�
	{
		DrawExtendGraph(384, 288, 768, 768, p_folder_media->GetDraw(0), false);

		DrawExtendGraph(1152, 288, 1536, 768, p_folder_media->GetDraw(1), false);

		if (gameSelect)
		{
			DrawBox(374 + now_checkgame * 768, 288, 778 + now_checkgame * 768, 768, 255, false);
		}
	}
	else if (gamenum == 0)		// 1��
	{
		DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(0), false);

		if (gameSelect)
		{
			DrawBox(758, 288, 1142, 768, 255, false);
		}
	}
	for (int i = 292; i != 1628; i += 4)
	{
		DrawLine(i, 910, i, 958, GetColor(255, 255, 255), true);
	}	
	DrawFormatString(384, 910, GetColor(255, 0, 0), "%s", p_folder_media->GetText(now_checkgame).c_str());		// �e�L�X�g
}


void GameList::DrawOption()
{
	DrawGraph(1400, 10, drawLauncherEnd[0], false);

	// �E�B���h�E�ύX���j���[�̃t���b�O�������Ă���Ƃ�
	if (windowSizeMenuFlag)
	{
		if (optionPerformerCount <= 40)
		{
			optionPerformerCount++;
		}
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * (optionPerformerCount / 1), drawWindow[optionTextFor], false);

			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * (optionPerformerCount / 1), drawSelectWin, false);
			}
		}
		DrawGraph(1550, 10 + numSize * (optionPerformerCount / 1), drawWindow[numSize], false);						// ���肳�ꂽ�摜���őO�ʂɂ��邽��
	}
	else
	{
		if (optionPerformerCount != 0)
		{
			optionPerformerCount--;
		}
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * (optionPerformerCount / 1), drawWindow[optionTextFor], false);

			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * (optionPerformerCount / 1), drawSelectWin, false);
			}
		}
		DrawGraph(1550, 10 + numSize * (optionPerformerCount / 1), drawWindow[numSize], false);						// ���肳�ꂽ�摜���őO�ʂɂ��邽��

		if (!gameSelect)
		{
			if (!endOrOption)
			{
				DrawBox(1400, 10, 1440, 50, 255, false);
			}
			else
			{
				DrawBox(1500, 10, 1540, 50, 255, false);
			}
		}
	}
}


void GameList::LauncherEnd()
{
	if (endFlag)
	{
		// ��̕�����NO��YES�̐؂�ւ�
		if (KeyData::Get(KEY_INPUT_LEFT) == 1)
		{
			endComfirm = false;
		}
		if (KeyData::Get(KEY_INPUT_RIGHT) == 1)
		{
			endComfirm = true;
		}

		// �G���^�[�L�[�������đI���󋵂ɉ�����
		if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1)
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

	drawLauncherEnd[0] = LoadGraph("dengen.png");
	drawLauncherEnd[1] = LoadGraph("�I���m�F.png");
	drawLauncherEnd[2] = LoadGraph("endtrue.png");
	drawLauncherEnd[3] = drawGameReady[3];

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

	gameReadyCheck = true;

	gameReady = false;

	gameReadyWait = 0;

	gamenum = (p_folder_name->GetGameNum() - 1);		// �z��Q�ƒl�Ɏg���̂Ŏ��O��-1����

	now_checkgame = 0;

	optionPerformerCount = 0;

	scrollNum = gamenum / 3;

	selectSideNum = 0;

	endFlag = false;

	endComfirm = false;

	endOrOption = false;
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
		DeleteGraph(drawLauncherEnd[i]);
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
	if (!createGameFlag && !endFlag)
	{
		if (gameReady)
		{
			DrawGraph(0, 0, drawGameReady[0], false);			// �K�E�X�t�B���^�[���{�����摜
			DrawExtendGraph(384, 96, 1536, 768, p_folder_media->GetMovie(now_checkgame), false);		// ����
			DrawFormatString(400, 48, 255, "%s", p_folder_name->GetGameListName()[now_checkgame].c_str());
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

			DrawOption();			// �E�B���h�E�I�v�V����
		}
	}

	if (endFlag)
	{
		DrawGraph(700, 520, drawLauncherEnd[1], false);
		DrawGraph(500, 720, drawLauncherEnd[2], false);
		DrawGraph(900, 720, drawLauncherEnd[3], false);
		// �I���󋵂ɉ����ĐF��ς���
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

	LauncherEnd();

	if (!createGameFlag && !endFlag)
	{
		KeyProcess();
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
		gameSelect = false;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1 && !windowSizeMenuFlag)
	{
		gameSelect = true;
	}
	if (!gameSelect)
	{
		if (KeyData::Get(KEY_INPUT_RIGHT) == 1)
		{
			endOrOption = true;
		}
		if (KeyData::Get(KEY_INPUT_LEFT) == 1)
		{
			endOrOption = false;
		}
	}

	// ���R���g���[����W�L�[�ŃE�B���h�E�ύX���j���[��\���܂��͔�\���ɂ�����
	if (KeyData::Get(KEY_INPUT_Z) == 1 && !gameSelect)
	{
		if (!endOrOption)
		{
			endFlag = true;
		}
		else
		{
			windowSizeMenuFlag = true;
		}
	}

	if (KeyData::Get(KEY_INPUT_ESCAPE == 1))
	{
		endFlag = true;
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

			gameSelect = true;

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

bool GameList::GetEndFlag()
{
	return endFlag;
}
