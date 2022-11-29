//=========================================================
//
//3Dゲーム[indexmeshfield.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"indexmeshfield.h"

//マクロ定義
#define INDEXMESH_BLOCK_X	(2)			//メッシュフィールドのブロック数（X）
#define INDEXMESH_SIZE_X	(200.0f)	//メッシュフィールドのサイズ（X）

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureIndexMeshfield = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffIndexMeshfield = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffIndexMeshField = NULL;		//インデックスバッファへのポインタ
D3DXVECTOR3 g_posIndexMeshfield;							//位置
D3DXVECTOR3 g_rotIndexMeshfield;							//向き
D3DXMATRIX g_mtxWorldIndexMeshfield;						//ワールドマトリックス
int g_nMaxMesh;												//最大メッシュ数

//===============================================
//メッシュフィールドの初期化処理
//===============================================
void InitIndexMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得
	int nCntMesh;
	g_nMaxMesh = 9;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureIndexMeshfield);

	//変数の初期化
	g_posIndexMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotIndexMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nMaxMesh,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffIndexMeshfield,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffIndexMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	//for (nCntMesh = 0; nCntMesh < INDEXMESH_BLOCK_X; nCntMesh++)
	//{
	//	pVtx[nCntMesh].pos = D3DXVECTOR3(-200.0f + INDEXMESH_SIZE_X * nCntMesh, 0.0f, 200.0f);
	//}

	pVtx[0].pos = D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
	pVtx[2].pos = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);
	pVtx[3].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	pVtx[8].pos = D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);

	//法線ベクトルの設定
	for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	{
		pVtx[nCntMesh].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//頂点カラーの設定
	for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	{
		pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャ座標の設定
	//for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	//{

	//}
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffIndexMeshfield->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffIndexMeshField,
		NULL);

	WORD * pldx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pldxBuffIndexMeshField->Lock(0, 0, (void**)&pldx, 0);

	//頂点番号データの設定
	pldx[0] = 3;
	pldx[1] = 0;
	pldx[2] = 4;
	pldx[3] = 1;
	pldx[4] = 5;
	pldx[5] = 2;
	pldx[6] = 2;
	pldx[7] = 6;
	pldx[8] = 6;
	pldx[9] = 3;
	pldx[10] = 7;
	pldx[11] = 4;
	pldx[12] = 8;
	pldx[13] = 5;

	//インデックスバッファをアンロックする
	g_pldxBuffIndexMeshField->Unlock();
}

//===============================================
//メッシュフィールドの終了処理
//===============================================
void UninitIndexMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureIndexMeshfield != NULL)
	{
		g_pTextureIndexMeshfield->Release();
		g_pTextureIndexMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffIndexMeshfield != NULL)
	{
		g_pVtxBuffIndexMeshfield->Release();
		g_pVtxBuffIndexMeshfield = NULL;
	}

	//インデックスバッファの破棄
	if (g_pldxBuffIndexMeshField != NULL)
	{
		g_pldxBuffIndexMeshField->Release();
		g_pldxBuffIndexMeshField = NULL;
	}
}

//===============================================
//メッシュフィールドの更新処理
//===============================================
void UpdateIndexMeshfield(void)
{

}

//===============================================
//メッシュフィールドの描画処理
//===============================================
void DrawIndexMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldIndexMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotIndexMeshfield.y, g_rotIndexMeshfield.x, g_rotIndexMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldIndexMeshfield, &g_mtxWorldIndexMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posIndexMeshfield.x, g_posIndexMeshfield.y, g_posIndexMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldIndexMeshfield, &g_mtxWorldIndexMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldIndexMeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffIndexMeshfield, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pldxBuffIndexMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureIndexMeshfield);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 
		0,
		9,
		0,
		12);
}
