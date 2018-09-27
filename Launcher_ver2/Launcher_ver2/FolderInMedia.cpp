#include "FolderInMedia.hpp"

using namespace std;

string FolderInMedia::ReadText(string textname)
{
	string L_Line = "";				// �ǂݍ��񂾍s�i1�s�j
	ifstream L_File;			// �ǂݍ��ރt�@�C��
	string textdata = "";	// �Ԃ�l

	string tempIn;		// �������ޗp�̉��u���ϐ�

	L_File.open(textname);		// �t�@�C���I�[�v��

	// �t�@�C���ǂݍ��ݎ��s
	if (L_File.fail())
	{
		textdata.resize(1);
		textdata =  "�e�L�X�g�f�[�^�Ȃ�";
	}
	else
	{
		getline(L_File, L_Line);
		
		tempIn = L_Line.substr(0, L_Line.size());
		textdata = tempIn.c_str();
	}
	// �t�@�C�������
	L_File.close();

	return textdata;
}

FolderInMedia::FolderInMedia(string pathname, vector<string> gamename, vector<string> moviename, vector<string> drawname, vector<string> textname, int gamenum)
{
	// vector�̈ꉞ������
	v_draw.clear();
	v_movie.clear();
	v_text.clear();

	noneData = LoadGraph("nonedata.png");


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
		v_movie.push_back(LoadGraph(tempPath.c_str()));
		// ���悪�Ȃ������ꍇnonedata������
		if (v_movie[i] == -1)
		{
			v_movie[i] = noneData;
		}


		// �摜�̓ǂݍ���
		tempPath = completePath;
		tempPath.operator+= (drawname[i]);
		v_draw.push_back(LoadGraph(tempPath.c_str()));
		// �f�[�^���Ȃ������ꍇ������nonedata������
		if (v_draw[i] == -1)
		{
			v_draw[i] = noneData;
		}


		// �e�L�X�g�f�[�^�̓ǂݍ���
		tempPath = completePath;
		tempPath.operator+= (textname[i]);
		v_text.push_back(ReadText(tempPath));
	}
}

FolderInMedia::~FolderInMedia()
{
	VECTOR_RELEASE(v_draw);
	VECTOR_RELEASE(v_movie);
	VECTOR_RELEASE(v_text);

	GRAPHIC_RELEASE(noneData);
}

const int FolderInMedia::GetMovie(const int listnum) const
{
	return v_movie[listnum];
}

const int FolderInMedia::GetDraw(const int listnum) const
{
	return v_draw[listnum];
}

const string FolderInMedia::GetText(const int listnum) const
{
	return v_text[listnum];
}
