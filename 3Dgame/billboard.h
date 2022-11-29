//=========================================================
//
//3Dゲーム[billboard.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _BILLBOARD_H_  //このマクロ定義がされてなかったら
#define _BILLBOARD_H_  //２重インクルード防止のマクロを定義する

//プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

#endif