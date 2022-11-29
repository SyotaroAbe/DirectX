//=========================================================
//
//3Dゲーム[station.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _STATION_H_  //このマクロ定義がされてなかったら
#define _STATION_H_  //２重インクルード防止のマクロを定義する

//モデル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 vecmove;	//移動ベクトル
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 rotDest;	//目的の向き
	float fRotDiff;			//目的の向きまでの差分
	bool bMove;				//動いたか
	int g_nIdxShadow = -1;
}Station;

//プロトタイプ宣言
void InitStation(void);
void UninitStation(void);
void UpdateStation(void);
void DrawStation(void);
Station * GetStation(void);

#endif