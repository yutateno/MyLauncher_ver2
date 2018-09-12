#include "FolderInMedia.h"

using namespace std;
namespace pb = projectbase;

vector<string> FolderInMedia::ReadText(string textname)
{
	int L_Count = 0;			// �ǂݍ��ݗp�i���s�ڂ�ǂݍ���ł��邩
	string L_Line;				// �ǂݍ��񂾍s�i1�s�j
	ifstream L_File;			// �ǂݍ��ރt�@�C��
	vector<string> textdata;	// �Ԃ�l

	int num = 0;		// �P�s�̕�����
	string tempIn;		// �������ޗp�̉��u���ϐ�
	int lineNum = 0;	// �������ݕ����̏����ʒu

	L_File.open(textname);		// �t�@�C���I�[�v��

	// �t�@�C���ǂݍ��ݎ��s
	if (L_File.fail())
	{
		textdata.resize(L_Count + 1);
		textdata[L_Count].operator+= ("�e�L�X�g�f�[�^�Ȃ�");
	}
	else
	{
		// ��s���ǂݍ���
		while (getline(L_File, L_Line))
		{	
			textdata.resize(L_Count + 6);		// ���̒����ł͉��s�����񂩂�����̂ő��߂ɐ������Ƃ�
			num = 0;
			lineNum = 0;

			for (int i = 0; i != L_Line.size(); ++i)
			{
				num++;
				// �������e�L�X�g�{�b�N�X���͂ݏo��
				if (num >= pb::TEXT_X_NUM)
				{
					// ���p�������ꍇ
					if (IsDBCSLeadByte(L_Line[i]) == 0)
					{
						tempIn = L_Line.substr(lineNum, i - lineNum);
						lineNum = i - 1;
						num = 0;
					}
					else
					{
						tempIn = L_Line.substr(lineNum, i - lineNum);
						lineNum = i;
						num = 0;
					}
					textdata[L_Count].operator+= (tempIn.c_str());
					L_Count++;	// ���̍s��
				}
			}
			tempIn = L_Line.substr(lineNum, L_Line.size() - lineNum);
			textdata[L_Count].operator+= (tempIn.c_str());

			L_Count++;	// ���̍s��

		}
	}
	// �t�@�C�������
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<vector<string>> drawname, vector<string> textname, int gamenum)
{
	nonedata = LoadGraph("nonedata.png");

	string completePath = "";
	string tempPath = "";

	int tempDraw = -1;
	int tempDrawIn[4];

	d_draw.resize(gamenum);		// �ǂݍ��ݐ������m��

	for (int i = 0; i != gamenum; ++i)
	{
		for (int j = 0; j != pb::DRAW_MEDIA_NUM; ++j)
		{
			tempDrawIn[j] = -1;
		}

		// �����܂œ������Ƃ̌J��Ԃ��Ȃ̂�completePath�ɓn��
		completePath = "";
		completePath.operator+= (pathname);
		completePath.operator+= (gamename[i]);
		completePath.operator+= ("\\");
		completePath.operator+= ("Launcher");
		completePath.operator+= ("\\");

		// �f�ނ��Ƃ�tempPath�ɕ�����𑝂₳����悤�ɂ���
		tempPath = completePath;

		// ����̓ǂݍ���
		tempPath.operator+= (moviename[i]);
		d_movie.push_back(LoadGraph(tempPath.c_str()));
		// ���悪�Ȃ������ꍇnonedata������
		if (d_movie[i] == -1)
		{
			d_movie[i] = nonedata;
		}

		// �摜�̓ǂݍ���
		for (int j = 0; j != drawname[i].size(); ++j)
		{
			tempPath = completePath;
			tempPath.operator+= (drawname[i][j]);
			tempDraw= LoadGraph(tempPath.c_str());
			GetGraphSize(tempDraw, &g_SizeX, &g_SizeY);		// �f�ނ̑傫���𒲂ׂ�
			// �f�ނ̑傫���Łu�w�i�v�u�e�L�X�g�{�b�N�X�v�u�^�C�g�����S�v�𔻒f
			if (g_SizeY >= pb::WINDOW_Y - 5)
			{
				tempDrawIn[0] = tempDraw;
			}
			else if (g_SizeY < pb::WINDOW_Y - 5 && g_SizeY >= pb::TEXT_BOX_LAST_Y - pb::TEXT_BOX_FIRST_Y - 5)
			{
				tempDrawIn[2] = tempDraw;
			}
			else if (g_SizeY < pb::TEXT_BOX_LAST_Y - pb::TEXT_BOX_FIRST_Y - 5 && g_SizeY >= pb::DRAW_GAMECHECK_SIZE_Y - 5)
			{
				tempDrawIn[3] = tempDraw;
			}
			else
			{
				tempDrawIn[1] = tempDraw;
			}
		}
		for (int j = 0; j != pb::DRAW_MEDIA_NUM; ++j)
		{
			// �f�[�^���Ȃ������ꍇ������nonedata������
			if (tempDrawIn[j] == -1)
			{
				tempDrawIn[j] = nonedata;
			}
			d_draw[i].push_back(tempDrawIn[j]);
		}

		// �e�L�X�g�f�[�^�̓ǂݍ���
		tempPath = completePath;
		tempPath.operator+= (textname[i]);
		d_text.push_back(ReadText(tempPath));
	}
}

FolderInMedia::~FolderInMedia()
{
	d_draw.clear();
	d_draw.shrink_to_fit();

	d_movie.clear();
	d_movie.shrink_to_fit();

	d_text.clear();
	d_text.shrink_to_fit();

	DeleteGraph(nonedata);
}

int FolderInMedia::GetMovie(int listnum)
{
	return d_movie[listnum];
}

vector<int> FolderInMedia::GetDraw(int listnum)
{
	return d_draw[listnum];
}

vector<string> FolderInMedia::GetText(int listnum)
{
	return d_text[listnum];
}
