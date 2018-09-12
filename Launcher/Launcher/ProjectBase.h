/* 多用しそうな者たち */
#include "DxLib.h"
#include <string>

#ifndef _PROJECT_BASE_H
#define _PROJECT_BASE_H
namespace projectbase
{
	const int WINDOW_X = 1920;
	const int WINDOW_Y = 1080;

	const int COLOR_WHITE	 = GetColor(255, 255, 255);
	const int COLOR_RED		 = GetColor(255, 0, 0);
	const int COLOR_BLOCK	 = GetColor(0, 0, 0);
	const int COLOR_SKY_BLUE = GetColor(137, 189, 222);

	const int DRAW_MEDIA_NUM	 = 4;	// 一つのゲームに対して描画をする画像数
	const int MOVEI_VOLUME_MAX	 = 10000;// 動画の最大音量

	const int TITLE_DRAW_CENTER_CENTER_X		 = 960;
	const int TITLE_DRAW_CENTER_CENTER_Y		 = 130;
	const int TITLE_DRAW_CIRCLE_X				 = 250;
	const int TITLE_DRAW_CIRCLE_Y				 = 120;
	const int TITLE_DRAW_RIGHT_CENTER_X			 = 1440;
	const int TITLE_DRAW_RIGHT_CENTER_Y			 = 130;
	const int TITLE_DRAW_RIGHT_X				 = 150;
	const int TITLE_DRAW_RIGHT_Y				 = 80;
	const int TITLE_DRAW_LEFT_CENTER_X			 = 480;
	const int TITLE_DRAW_LEFT_CENTER_Y			 = 130;
	const int TITLE_DRAW_LEFT_X					 = 160;
	const int TITLE_DRAW_LEFT_Y					 = 80;
	const int TITLE_DRAW_SECOND_LEFT_CENTER_X	 = 200;
	const int TITLE_DRAW_SECOND_LEFT_CENTER_Y	 = 130;
	const int TITLE_DRAW_SECOND_LEFT_X			 = 100;
	const int TITLE_DRAW_SECOND_LEFT_Y			 = 50;
	const int TITLE_DRAW_SECOND_RIGHT_CENTER_X	 = 1720;
	const int TITLE_DRAW_SECOND_RIGHT_CENTER_Y	 = 130;
	const int TITLE_DRAW_SECOND_RIGHT_X			 = 100;
	const int TITLE_DRAW_SECOND_RIGHT_Y			 = 50;

	const int MOVIE_CENTER_X	 = 740;
	const int MOVIE_CENTER_Y	 = 640;
	const int MOVIE_LONG_X		 = 660;
	const int MOVIE_LONG_Y		 = 380;
	const int MOVIE_MOVE_FLAME	 = 500;

	const int TEXT_BOX_FIRST_X	 = 1440;
	const int TEXT_BOX_FIRST_Y	 = 330;
	const int TEXT_BOX_LAST_X	 = 1860;
	const int TEXT_BOX_LAST_Y	 = 960;
	const int TEXT_X			 = 1450;
	const int TEXT_Y			 = 360;
	const int TEXT_SPACE		 = 20;
	const int TEXT_X_NUM		 = 44;

	const int DRAW_GAMECHECK_SIZE_X		 = 600;
	const int DRAW_GAMECHECK_SIZE_Y		 = 400;
	const int DRAW_GAMECHECK_AREA_X		 = WINDOW_X / 2 - DRAW_GAMECHECK_SIZE_X / 2;
	const int DRAW_GAMECHECK_AREA_Y		 = WINDOW_Y / 2 - DRAW_GAMECHECK_SIZE_Y / 2;
	const int DRAW_GAMECHECK_TEXTAREA_X	 = 200;
	const int DRAW_GAMECHECK_TEXTAREA_Y	 = 140;

	const int CHANGE_FONT_DATA_SIZE = 32;	// 起動確認用のフォントサイズ
}
#endif // !_PROJECT_BASE_H