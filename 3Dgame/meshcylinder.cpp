//=========================================================
//
//3Dゲーム[meshcylinder.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"meshcylinder.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshcylinder = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshcylinder = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshcylinder = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshcylinder;							//位置
D3DXVECTOR3 g_rotMeshcylinder;							//向き
D3DXMATRIX g_mtxWorldMeshcylinder;						//ワールドマトリックス

//===============================================
//メッシュシリンダーの初期化処理
//===============================================
void InitMeshcylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得
	int nCntMesh;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshcylinder);

	//変数の初期化
	g_posMeshcylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshcylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 18,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshcylinder,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshcylinder->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[1].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.25f) * 200.0f);
	pVtx[2].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.5f) * 200.0f);
	pVtx[3].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.75f) * 200.0f);
	pVtx[4].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.0f) * 200.0f);
	pVtx[5].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.75f) * 200.0f);
	pVtx[6].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.5f) * 200.0f);
	pVtx[7].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.25f) * 200.0f);
	pVtx[8].pos = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[9].pos = D3DXVECTOR3(-sinf(D3DX_PI * 1.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[10].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.25f) * 200.0f);
	pVtx[11].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.5f) * 200.0f);
	pVtx[12].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.75f) * 200.0f);
	pVtx[13].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.0f) * 200.0f);
	pVtx[14].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.75f) * 200.0f);
	pVtx[15].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.5f) * 200.0f);
	pVtx[16].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.25f) * 200.0f);
	pVtx[17].pos = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 1.0f) * 200.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[1].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.25f) * 200.0f);
	pVtx[2].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.5f) * 200.0f);
	pVtx[3].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.75f) * 200.0f);
	pVtx[4].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 0.0f) * 200.0f);
	pVtx[5].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.75f) * 200.0f);
	pVtx[6].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.5f) * 200.0f);
	pVtx[7].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 200.0f, 50.0f, cosf(-D3DX_PI * 0.25f) * 200.0f);
	pVtx[8].nor = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 50.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[9].nor = D3DXVECTOR3(-sinf(D3DX_PI * 1.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 1.0f) * 200.0f);
	pVtx[10].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.25f) * 200.0f);
	pVtx[11].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.5f) * 200.0f);
	pVtx[12].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.75f) * 200.0f);
	pVtx[13].nor = D3DXVECTOR3(sinf(D3DX_PI * 0.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 0.0f) * 200.0f);
	pVtx[14].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.75f) * 200.0f);
	pVtx[15].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.5f) * 200.0f);
	pVtx[16].nor = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 200.0f, 0.0f, cosf(-D3DX_PI * 0.25f) * 200.0f);
	pVtx[17].nor = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 200.0f, 0.0f, cosf(D3DX_PI * 1.0f) * 200.0f);

	//for (nCntMesh = 0; nCntMesh < 18; nCntMesh++)
	//{
	//	pVtx[nCntMesh].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//}

	//頂点カラーの設定
	for (nCntMesh = 0; nCntMesh < 18; nCntMesh++)
	{
		pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.375f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.625f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.875f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.125f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.375f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.625f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.75f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(0.875f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffMeshcylinder->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshcylinder,
		NULL);

	WORD * pldx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pldxBuffMeshcylinder->Lock(0, 0, (void**)&pldx, 0);

	//頂点番号データの設定
	pldx[0] = 9;
	pldx[1] = 0;
	pldx[2] = 10;
	pldx[3] = 1;
	pldx[4] = 11;
	pldx[5] = 2;
	pldx[6] = 12;
	pldx[7] = 3;
	pldx[8] = 13;
	pldx[9] = 4;
	pldx[10] = 14;
	pldx[11] = 5;
	pldx[12] = 15;
	pldx[13] = 6;
	pldx[14] = 16;
	pldx[15] = 7;
	pldx[16] = 17;
	pldx[17] = 8;

	//インデックスバッファをアンロックする
	g_pldxBuffMeshcylinder->Unlock();
}

//===============================================
//メッシュシリンダーの終了処理
//===============================================
void UninitMeshcylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshcylinder != NULL)
	{
		g_pTextureMeshcylinder->Release();
		g_pTextureMeshcylinder = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshcylinder != NULL)
	{
		g_pVtxBuffMeshcylinder->Release();
		g_pVtxBuffMeshcylinder = NULL;
	}

	//インデックスバッファの破棄
	if (g_pldxBuffMeshcylinder != NULL)
	{
		g_pldxBuffMeshcylinder->Release();
		g_pldxBuffMeshcylinder = NULL;
	}
}

//===============================================
//メッシュシリンダーの更新処理
//===============================================
void UpdateMeshcylinder(void)
{

}

//===============================================
//メッシュシリンダーの描画処理
//===============================================
void DrawMeshcylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshcylinder);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshcylinder.y, g_rotMeshcylinder.x, g_rotMeshcylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshcylinder, &g_mtxWorldMeshcylinder, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshcylinder.x, g_posMeshcylinder.y, g_posMeshcylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshcylinder, &g_mtxWorldMeshcylinder, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshcylinder);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshcylinder, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pldxBuffMeshcylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshcylinder);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		18,
		0,
		18);
}
