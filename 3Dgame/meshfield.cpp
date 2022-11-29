//=========================================================
//
//3Dゲーム[meshfield.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"meshfield.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posMeshfield;							//位置
D3DXVECTOR3 g_rotMeshfield;							//向き
D3DXMATRIX g_mtxWorldMeshfield;						//ワールドマトリックス

//===============================================
//メッシュフィールドの初期化処理
//===============================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshfield);

	//変数の初期化
	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
	pVtx[4].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
	pVtx[6].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
	pVtx[7].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	pVtx[8].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	pVtx[9].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, -200.0f);
	pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[12].pos = D3DXVECTOR3(200.0f, 0.0f, -200.0f);
	pVtx[13].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[10].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[12].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfield->Unlock();
}

//===============================================
//メッシュフィールドの終了処理
//===============================================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}
}

//===============================================
//メッシュフィールドの更新処理
//===============================================
void UpdateMeshfield(void)
{

}

//===============================================
//メッシュフィールドの描画処理
//===============================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
}
