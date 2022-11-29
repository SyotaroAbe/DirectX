//=========================================================
//
//3Dゲーム[wall.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _WALL_H_  //このマクロ定義がされてなかったら
#define _WALL_H_  //２重インクルード防止のマクロを定義する

//壁の種類
typedef enum
{
	WALLTYPE_NORMAL = 0,	//通常
	WALLTYPE_INVISIBLE,		//透明
	WALLTYPE_MAX
}WALLTYPE;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);

#endif