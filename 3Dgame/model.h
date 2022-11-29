//=========================================================
//
//3Dゲーム[model.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _MODEL_H_  //このマクロ定義がされてなかったら
#define _MODEL_H_  //２重インクルード防止のマクロを定義する

//マクロ定義
#define MAX_TEXTURE			(24)		//最大テクスチャ数
#define ROT_DIFF_PI			(2.0f)		//角度の値の補正
#define ROT_CAMERA			(1.0f)		//カメラの向きに合わせて動かす
#define ROT_CAMERA_DIFF		(0.1f)		//角度の補正係数（数が大きい程素早く変わる）
#define MIN_VTX				(900.0f)	//vtx最小値初期値
#define MAX_VTX				(-900.0f)	//vtx最大値初期値

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
}Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model * GetModel(void);

#endif