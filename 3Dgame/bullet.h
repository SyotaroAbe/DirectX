//=========================================================
//
//3Dゲーム[bullet.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _BULLET_H_  //このマクロ定義がされてなかったら
#define _BULLET_H_  //２重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define BULLET_LIFE		(50)	//弾の体力

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void GetWall(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, int nCntWall);

#endif