//=========================================================
//
//3Dゲーム[camera.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _CAMERA_H_  //このマクロ定義がされてなかったら
#define _CAMERA_H_  //２重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define ZERO			(0.0f)		//0

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//目的の向き
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	float fLength;
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera * GetCamera(void);

#endif