//=========================================================
//
//3Dゲーム[wall.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"wall.h"

//マクロ定義
#define MAX_WALL	(2)		//最大壁数

//壁構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	int g_nWallType;			//タイプ
	D3DXMATRIX g_mtxWorldWall;	//ワールドマトリックス
}Wall;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
Wall g_aWall[MAX_WALL];							//壁の情報

//===============================================
//壁の初期化処理
//===============================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得
	int nCntWall;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	//変数の初期化
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-200.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//===============================================
//壁の終了処理
//===============================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//===============================================
//壁の更新処理
//===============================================
void UpdateWall(void)
{

}

//===============================================
//壁の描画処理
//===============================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aWall[nCntWall].g_mtxWorldWall);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorldWall, &g_aWall[nCntWall].g_mtxWorldWall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorldWall, &g_aWall[nCntWall].g_mtxWorldWall, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].g_mtxWorldWall);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

//===============================================
//壁の設定処理
//===============================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	VERTEX_3D * pVtx;   //頂点情報へのポインタ
	int nCntWall;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = pos;
		g_aWall[nCntWall].rot = rot;
		g_aWall[nCntWall].g_nWallType = type;

		if (g_aWall[nCntWall].g_nWallType == WALLTYPE_NORMAL)
		{

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if (g_aWall[nCntWall].g_nWallType == WALLTYPE_INVISIBLE)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		break;
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}