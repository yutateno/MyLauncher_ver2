#include "FolderInMedia.hpp"

using namespace std;
namespace pb = projectbase;

string FolderInMedia::ReadText(string textname)
{
	string L_Line;				// �ǂݍ��񂾍s�i1�s�j
	ifstream L_File;			// �ǂݍ��ރt�@�C��
	string textdata = "";	// �Ԃ�l

	string tempIn;		// �������ޗp�̉��u���ϐ�

	L_File.open(textname);		// �t�@�C���I�[�v��

	// �t�@�C���ǂݍ��ݎ��s
	if (L_File.fail())
	{
		//textdata.resize(1);
		textdata =  "�e�L�X�g�f�[�^�Ȃ�";
	}
	else
	{
		getline(L_File, L_Line);
			
		// ���p�������ꍇ
		tempIn = L_Line.substr(0, L_Line.size());
		textdata = tempIn.c_str();
	}
	// �t�@�C�������
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<string> drawname, vector<string> textname, int gamenum)
{
	nonedata = LoadGraph("nonedata.png");


	string completePath = "";
	string tempPath = "";


	int tempDraw = -1;


	for (int i = 0; i != gamenum; ++i)
	{
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
		tempPath = completePath;
		tempPath.operator+= (drawname[i]);
		d_draw.push_back(LoadGraph(tempPath.c_str()));
		// �f�[�^���Ȃ������ꍇ������nonedata������
		if (d_draw[i] == -1)
		{
			d_draw[i] = nonedata;
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

int FolderInMedia::GetDraw(int listnum)
{
	return d_draw[listnum];
}

string FolderInMedia::GetText(int listnum)
{
	return d_text[listnum];
}
