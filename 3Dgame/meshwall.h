//=========================================================
//
//3Dゲーム[meshwall.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _MESHWALL_H_  //このマクロ定義がされてなかったら
#define _MESHWALL_H_  //２重インクルード防止のマクロを定義する

//マクロ定義
#define MAX_MESHWALL	(4)			//最大壁数
#define WALL_SIZE		(-1980.0f)	//壁サイズ

//壁構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	int nMeshwallType;				//タイプ
	D3DXMATRIX mtxWorldMeshwall;	//ワールドマトリックス
	bool bUse;
}MeshWall;

//壁の種類
typedef enum
{
	MESHWALLTYPE_NORMAL = 0,	//通常
	MESHWALLTYPE_INVISIBLE,		//透明
	MESHWALLTYPE_MAX
}MESHWALLTYPE;

//プロトタイプ宣言
void InitMeshwall(void);
void UninitMeshwall(void);
void UpdateMeshwall(void);
void DrawMeshwall(void);
void SetMeahwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);

#endif