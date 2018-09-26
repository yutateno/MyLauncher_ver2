/* 多用しそうな者たち */


// インクルード
#include "DxLib.h"
#include <string>


// 一度だけ通す
#ifndef _PROJECT_BASE_H
#define _PROJECT_BASE_H
namespace projectbase
{
	const int WINDOW_X = 1920;
	const int WINDOW_Y = 1080;
}
#endif // !_PROJECT_BASE_H


// マクロ
#define POINTER_RELEASE(p) { if(p!=NULL) {delete (p); (p)=NULL; } }
#define GRAPH_RELEASE(p) { if(p!=-1) {DeleteGraph(p); (p)=0; } }
#define VECTOR_RELEASE(p) { p.clear(); p.shrink_to_fit(); }


// debugマクロ
// #define DEBUG_PRINTFDX;