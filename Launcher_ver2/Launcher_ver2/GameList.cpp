#include "GameList.hpp"

namespace ps = padstick;


// �Q�[���I����ʂ̃Q�[���Ɋւ���`��
void GameList::DrawGameFileScroll()
{
	// �Q�[���̌��ɂ����UI��ύX
	if (gameNum >= 3)			// 4�ȏ�
	{
		selectSideNum = now_checkGame / 3;			// ������ڂ��m�F
		

		DrawExtendGraph(192, 288, 576, 768, p_folder_media->GetDraw(3 * selectSideNum), false);					// ��


		// �^�񒆂ɕ��ׂ�Q�[�������邩�m�F
		if (gameNum >= 3 * selectSideNum + 1)
		{
			DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(3 * selectSideNum + 1), false);		// �^��
		}


		// �E�ɕ��ׂ�Q�[�������邩�m�F
		if (gameNum >= 3 * selectSideNum + 2)
		{
			DrawExtendGraph(1344, 288, 1728, 768, p_folder_media->GetDraw(3 * selectSideNum + 2), false);		// �E
		}


		// 1��ڂ̎�
		if (selectSideNum == 0)
		{
			DrawExtendGraph(1872, 288, 2256, 768, p_folder_media->GetDraw(3 * selectSideNum + 3), false);		// �E�[��4�ڂ̃Q�[�����`�����Z����
		}
		// �Ō�̗�̎�
		else if (selectSideNum == gameNum / 3)
		{
			DrawExtendGraph(-336, 288, 48, 768, p_folder_media->GetDraw(3 * selectSideNum - 1), false);			// ���[�Ɉ�O�̗�̍Ō�̃Q�[�����`�����Z����
		}
		// ����ȊO�̎�
		else
		{
			DrawExtendGraph(-336, 288, 48, 768, p_folder_media->GetDraw(3 * selectSideNum - 1), false);			// ���[�Ɉ�O�̗�̍Ō�̃Q�[�����`�����Z����
			DrawExtendGraph(1872, 288, 2256, 768, p_folder_media->GetDraw(3 * selectSideNum + 3), false);		// �E�[��4�ڂ̃Q�[�����`�����Z����
		}


		// �Q�[���ɃJ�[�\���𓖂ĂĂ���
		if (gameSelect)
		{
			DrawBox(182 + (now_checkGame - selectSideNum * 3) * 576, 288, 586 + (now_checkGame - selectSideNum * 3) * 576, 768, 255, false);		// �t�H�[�J�X�𕪂���₷���悤�Ƀ{�b�N�X�ň͂�
		}

	}
	else if (gameNum == 2)		// 3�ȏ�
	{
		DrawExtendGraph(192,	288,	576,	768, p_folder_media->GetDraw(0), false);			// ��
		DrawExtendGraph(768,	288,	1152,	768, p_folder_media->GetDraw(1), false);			// �^��
		DrawExtendGraph(1344,	288,	1728,	768, p_folder_media->GetDraw(2), false);			// �E


		// �Q�[���ɃJ�[�\���𓖂ĂĂ���
		if (gameSelect)
		{
			DrawBox(182 + now_checkGame * 576, 288, 586 + now_checkGame * 576, 768, 255, false);			// �t�H�[�J�X�𓖂Ăĕ�����₷���悤��
		}

	}
	else if (gameNum == 1)		// 2�ȏ�
	{
		DrawExtendGraph(384,	288,	768,	768, p_folder_media->GetDraw(0), false);				// ��
		DrawExtendGraph(1152,	288,	1536,	768, p_folder_media->GetDraw(1), false);				// �^��


		// �Q�[���ɃJ�[�\���𓖂ĂĂ���
		if (gameSelect)
		{
			DrawBox(374 + now_checkGame * 768, 288, 778 + now_checkGame * 768, 768, 255, false);			// �t�H�[�J�X�𓖂ĂĂ��
		}

	}
	else if (gameNum == 0)		// 1��
	{
		DrawExtendGraph(768, 288, 1152, 768, p_folder_media->GetDraw(0), false);			// �Q�[��


		// �Q�[���ɃJ�[�\���𓖂ĂĂ���
		if (gameSelect)
		{
			DrawBox(758, 288, 1142, 768, 255, false);			// ������₷���悤��
		}
	}


	// �Q�[���Ɋւ���e�L�X�g��\��
	for (int i = 292; i != 1628; i += 4)
	{
		DrawLine(i, 910, i, 958, GetColor(255, 255, 255), true);		// ����\�����܂��鉉�o
	}	
	DrawFormatString(384, 910, GetColor(255, 0, 0), "%s", p_folder_media->GetText(now_checkGame).c_str());		// �e�L�X�g

}


// �I�v�V������ʂ̕`��
void GameList::DrawOption()
{
	DrawGraph(1400, 10, drawLauncherEnd[0], false);				// �d���{�^��

	static int optionPerformerCount = 0;		// �E�B���h�E�T�C�Y�I�v�V�����̉��o�p�ϐ�

	// �E�B���h�E�ύX���j���[�̃t���b�O�������Ă���Ƃ�
	if (windowSizeMenuFlag)
	{
		// ���o�p
		if (optionPerformerCount <= 40)
		{
			optionPerformerCount++;
		}


		// �E�B���h�E�T�C�Y��\��
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * optionPerformerCount, drawWindow[optionTextFor], false);				// �E�B���h�E�T�C�Y�R�}���h


			// �I�����Ă�����̂�������₷���悤�Ɍ���R�}���h�̍��W���ړ�
			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * optionPerformerCount, drawSelectWin, false);						// �E�B���h�E�T�C�Y��ς��錈��R�}���h
			}

		}


		DrawGraph(1550, 10 + numSize * optionPerformerCount, drawWindow[numSize], false);						// ���肳�ꂽ�摜���őO�ʂɂ��邽��
	}
	else
	{
		// ���o�p
		if (optionPerformerCount != 0)
		{
			optionPerformerCount--;
		}


		// �E�B���h�E�T�C�Y��\��
		for (optionTextFor = SizeWindow::Select::Default; optionTextFor <= SizeWindow::Select::Ninth; ++optionTextFor)
		{
			DrawGraph(1550, 10 + optionTextFor * optionPerformerCount, drawWindow[optionTextFor], false);				// �E�B���h�E�R�}���h


			// �I�����Ă�����̂�������₷���悤�Ɍ���R�}���h�̍��W���ړ�
			if (numSize == optionTextFor)
			{
				DrawGraph(1500, 10 + optionTextFor * optionPerformerCount, drawSelectWin, false);					// �E�B���h�E�T�C�Y��ς��錈��R�}���h
			}

		}


		DrawGraph(1550, 10 + numSize * optionPerformerCount, drawWindow[numSize], false);						// ���肳�ꂽ�摜���őO�ʂɂ��邽��


		// �Q�[���ɃJ�[�\�����������Ă��Ȃ�
		if (!gameSelect)
		{
			// �J�[�\�����d���ɓ������Ă���
			if (!endCommandForcus)
			{
				DrawBox(1400, 10, 1440, 50, 255, false);		// �t�H�[�J�X
			}
			// �J�[�\�����E�B���h�E�T�C�Y�ɓ������Ă���
			else
			{
				DrawBox(1500, 10, 1540, 50, 255, false);		// �t�H�[�J�X
			}

		}

	}

}


// ����Ɋւ���Ǘ�
void GameList::KeyProcess()
{
	for (int i = 0; i != PadData::GetPadNum(); ++i)
	{
		if (!endFlag)
		{
			// �Q�[���I���̑���
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
			// �����`���[�̏I���̑���
			LauncherEnd(PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, false)
				, PadData::GetStickCheck(ps::XINPUT_LEFT_THUMB_X, i, true), PadData::Get(XINPUT_BUTTON_A, i));

		}

	}

	if (!endFlag)
	{
		// �Q�[���I���̑���
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
		// �����`���[�I���̑���
		LauncherEnd(KeyData::Get(KEY_INPUT_LEFT), KeyData::Get(KEY_INPUT_RIGHT), KeyData::Get(KEY_INPUT_Z));

	}
}


// �I�v�V������ʂ̑���
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

	// ���R���g���[����W�L�[�ŃE�B���h�E�ύX���j���[��\���܂��͔�\���ɂ�����
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


	// �E�B���h�E�ύX���j���[�̃t���b�O�������Ă���Ƃ�
	if (windowSizeMenuFlag)
	{
		optionTextFor = 0;
		static int doubleSelectWait = 0;		// �_�u���N���b�N�������Ȃ�(�����̃f�o�C�X���瓯���Ɏ擾���Ă��邽��)
		doubleSelectWait++;
		// ��ALT�ƃe���L�[�ŃT�C�Y��ύX���鏀��
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

		// �G���^�[�L�[�ŉ�ʃT�C�Y���w�肵�����̂ɕύX
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


// �Q�[���N���̑���Ɋւ���
void GameList::GameUpdate(int right, int left, int dicision)
{
	// �Q�[�����N�����Ă��Ȃ��ăQ�[���̏�����ʂɂ��Ȃ��Ƃ��Ɍ���R�}���h����������
	if ((dicision == 1) && !createGameFlag && !gameReady)
	{
		gameReady = true;															// �Q�[���̏�����ʂɓ�������t���b�O�𗧂Ă�
		GetDrawScreenGraph(0, 0, 1920, 1080, drawGameReady[0]);						// ���݂̉�ʂ��L���v�`������
		GraphFilter(drawGameReady[0], DX_GRAPH_FILTER_GAUSS, 16, 1400);				// ���݂̉�ʂɃK�E�X�t�B���^�����Ăڂ���
		PlayMovieToGraph(p_folder_media->GetMovie(now_checkGame));					// ������Đ�����
	}


	// �Q�[���N���̏������
	if (gameReady)
	{
		static int doubleSelectWait = 0;		// �_�u���N���b�N�������Ȃ�(�����̃f�o�C�X���瓯���Ɏ擾���Ă��邽��)
		doubleSelectWait++;


		// �E�{�^����I������R�}���h��������
		if (right == 1)
		{
			gameReadyCheck = false;						// �Q�[�����N�����Ȃ����ɃJ�[�\��
		}


		// ���{�^����I������R�}���h��������
		if (left == 1)
		{
			gameReadyCheck = true;						// �Q�[�����N��������ɃJ�[�\��
		}


		// ����R�}���h��������
		if (dicision == 1 && doubleSelectWait >= 10)
		{
			// �߂��I��
			if (!gameReadyCheck)
			{
				gameReady = false;													// �Q�[���̏�����ʂ���߂�
				doubleSelectWait = 0;												// �_�u���N���b�N�h�~��������
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkGame));			// ������~�߂�
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);		// ����̍Đ��ʒu���ŏ��ɖ߂�
				gameReadyCheck = true;
			}
			// �Q�[���N����I��
			else
			{
				createGameFlag = true;																				// �Q�[���̋N���������n�߂�
				PauseMovieToGraph(p_folder_media->GetMovie(now_checkGame));											// ������~�߂�
				SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);										// ����̍Đ��ʒu���ŏ��ɖ߂�
				p_folder_game->Process(p_folder_name->GetPathName(), p_folder_name->GetFolderName(now_checkGame));	// �Q�[���̋N������
			}
		}
	}


	// ��ԉE�łȂ��Ƃ��E�̃Q�[���̏ڍׂֈړ�����
	if (right == 1 && now_checkGame != gameNum && !gameReady)
	{
		now_checkGame++;													// ���̊m�F���Ă�Q�[�������ɑJ��
	}


	// ��ԍ��łȂ��Ƃ����̃Q�[���̏ڍׂֈړ�����
	if (left == 1 && now_checkGame != 0 && !gameReady)
	{
		now_checkGame--;													// ���̊m�F���Ă�Q�[������O�ɑJ��
	}

}


// �����`���[�̏I��
void GameList::LauncherEnd(int left, int right, int dicision)
{
	if (endFlag)
	{
		// ��̕�����NO��YES�̐؂�ւ�
		if (left == 1)
		{
			endComfirm = false;
		}
		if (right == 1)
		{
			endComfirm = true;
		}

		// �G���^�[�L�[�������đI���󋵂ɉ�����
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



// �R���X�g���N�^
GameList::GameList(int defaultXSize, int defaultYSize)
{
	// �|�C���^�[����
	p_folder_game = NULL;
	p_folder_name = NULL;
	p_folder_media = NULL;

	p_folder_game = new FolderInGame();
	p_folder_name = new FolderName();
	p_folder_media = new FolderInMedia(p_folder_name->GetPathName(), p_folder_name->GetGameListName()
		, p_folder_name->GetMovieListName(), p_folder_name->GetDrawListName()
		, p_folder_name->GetTextListName(), p_folder_name->GetGameNum());


	// �摜��ۑ�����ϐ�
	drawWindow[SizeWindow::Default]	 = LoadGraph("�S���.png");
	drawWindow[SizeWindow::First]	 = LoadGraph("640x480.png");
	drawWindow[SizeWindow::Second]	 = LoadGraph("768x576.png");
	drawWindow[SizeWindow::Third]	 = LoadGraph("1024x768.png");
	drawWindow[SizeWindow::Fourth]	 = LoadGraph("1280x720.png");
	drawWindow[SizeWindow::Fifth]	 = LoadGraph("1366x768.png");
	drawWindow[SizeWindow::Sixth]	 = LoadGraph("1920x1080.png");
	drawWindow[SizeWindow::Seventh]	 = LoadGraph("2048x1536.png");
	drawWindow[SizeWindow::Eighth]	 = LoadGraph("2560x1440.png");
	drawWindow[SizeWindow::Ninth]	 = LoadGraph("3200x2400.png");

	drawSelectWin = LoadGraph("windowselect.png");

	drawGameReady[0] = MakeScreen(1920, 1080);
	drawGameReady[1] = LoadGraph("gamestart.png");
	drawGameReady[2] = LoadGraph("start.png");
	drawGameReady[3] = LoadGraph("back.png");

	drawLauncherEnd[0] = LoadGraph("dengen.png");
	drawLauncherEnd[1] = LoadGraph("�I���m�F.png");
	drawLauncherEnd[2] = LoadGraph("endtrue.png");
	drawLauncherEnd[3] = drawGameReady[3];


	// �Q�[���ꗗ�Ɋւ���
	gameNum = (p_folder_name->GetGameNum() - 1);		// �z��Q�ƒl�Ɏg���̂Ŏ��O��-1����
	now_checkGame = 0;
	selectSideNum = 0;


	// �Q�[���̋N���Ɋւ���
	gameReady = false;
	gameReadyCheck = true;
	createGameFlag = false;


	// �����`���[�I���Ɋւ���
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


	// �E�B���h�E�T�C�Y�ύX�Ɋւ���
	default_xSize = defaultXSize;
	default_ySize = defaultYSize;
	numSize = 0;
	xSize = default_xSize;
	ySize = default_ySize;
	gameSelect = true;
	windowSizeMenuFlag = false;
	optionTextFor = 0;	
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
		DrawFormatString(500, 500, GetColor(0, 0, 0), "�Q�[���t�@�C�������݂��܂���B���b�㋭���I�����܂��B\nDon't Game Folder. Force Quit An Application.");
	}
	else
	{
		// �Q�[�����N�����Ă��Ȃ��Ƃ�
		if (!createGameFlag && !endFlag)
		{
			if (gameReady)
			{
				DrawGraph(0, 0, drawGameReady[0], false);			// �K�E�X�t�B���^�[���{�����摜
				DrawExtendGraph(384, 96, 1536, 768, p_folder_media->GetMovie(now_checkGame), false);		// ����
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
#ifdef DEBUG_PRINTFDX
	printfDx("%d\n", forceEndCount);
#endif // DEBUG_PRINTFDX
}


void GameList::Process()
{
	if (forceEnd)
	{
		static int forceEndCount = 0;		// �����I���̊m�F��ʂ̕\������
		forceEndCount++;
		if (forceEndCount >= 300)
		{
			launcher_end = true;
		}
	}
	else
	{
		// �Q�[�����I��������
		if (createGameFlag && !p_folder_game->GetbResult())
		{
			createGameFlag = false;
			gameReady = false;
			gameReadyCheck = false;
		}

		// ���݂̓���̍Đ����I�������
		if (gameReady && !createGameFlag && GetMovieStateToGraph(p_folder_media->GetMovie(now_checkGame)) == 0)
		{
			SeekMovieToGraph(p_folder_media->GetMovie(now_checkGame), 0);			// ����̍Đ��ʒu���ŏ��ɖ߂�
			PlayMovieToGraph(p_folder_media->GetMovie(now_checkGame));
		}

		if (!createGameFlag)
		{
			KeyProcess();
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
