//=========================================================
//
//3Dゲーム[field.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _FIELD_H_  //このマクロ定義がされてなかったら
#define _FIELD_H_  //２重インクルード防止のマクロを定義する

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif