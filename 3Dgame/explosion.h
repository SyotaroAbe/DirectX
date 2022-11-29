//=========================================================
//
//3Dゲーム[explosion.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _EXPLOSION_H_  //このマクロ定義がされてなかったら
#define _EXPLOSION_H_  //２重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

#endif