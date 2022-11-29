//=========================================================
//
//3Dゲーム[shadow.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _SHADOW_H_  //このマクロ定義がされてなかったら
#define _SHADOW_H_  //２重インクルード防止のマクロを定義する

#include "main.h"

//影の種類
typedef enum
{
	SHADOWTYPE_PLAYER = 0,	//プレイヤー
	SHADOWTYPE_BULLET,		//弾
	SHADOWTYPE_MAX
}SHADOWTYPE;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nTdxShadow, D3DXVECTOR3 pos, int type, bool bUse);

#endif