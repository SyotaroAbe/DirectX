//=========================================================
//
//3Dゲーム[shadow.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"shadow.h"

//マクロ定義
#define MAX_SHADOW	(256)	//影の最大数

//影構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX g_mtxWorldShadow;	//ワールドマトリックス
	int nType;						//種類
	bool bUse;						//使用しているかどうか
}Shadow;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;        //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;   //頂点バッファへのポインタ
Shadow g_aShadow[MAX_SHADOW];						//影の情報

//===============================================
//影の初期化処理
//===============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();    //デバイスの取得
	int nCntShadow;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//変数の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//===============================================
//影の終了処理
//===============================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//===============================================
//影の更新処理
//===============================================
void UpdateShadow(void)
{

}

//===============================================
//影の描画処理
//===============================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	int nCntShadow = -1;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{//影が使用されている

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].g_mtxWorldShadow);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].g_mtxWorldShadow, &g_aShadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].g_mtxWorldShadow, &g_aShadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].g_mtxWorldShadow);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===============================================
//影の設定処理
//===============================================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}

	return nCntShadow;
}

//===============================================
//影の位置設定処理
//===============================================
void SetPositionShadow(int nTdxShadow, D3DXVECTOR3 pos, int type, bool bUse)
{
	VERTEX_3D * pVtx;   //頂点情報へのポインタ
	int nCntShadow;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (nCntShadow == nTdxShadow)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].nType = type;
			g_aShadow[nCntShadow].bUse = bUse;

			if (g_aShadow[nCntShadow].nType == SHADOWTYPE_PLAYER)
			{//プレイヤーの影
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
				pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
				pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
				pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
			}
			else if (g_aShadow[nCntShadow].nType == SHADOWTYPE_BULLET)
			{//弾の影
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
				pVtx[1].pos = D3DXVECTOR3(20.0f, 0.0f, 20.0f);
				pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
				pVtx[3].pos = D3DXVECTOR3(20.0f, 0.0f, -20.0f);
			}
			break;
		}
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}