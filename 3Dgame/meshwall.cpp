//=========================================================
//
//3Dゲーム[meshwall.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"meshwall.h"
#include"bullet.h"
#include"model.h"
#include"camera.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMeshwall = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshwall = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshwall = NULL;	//インデックスバッファへのポインタ
MeshWall g_aMeshWall[MAX_MESHWALL];					//壁の情報

//===============================================
//メッシュウォールの初期化処理
//===============================================
void InitMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得
	int nCntMeshWall;
	int nCntMesh;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshwall);

	//変数の初期化
	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshwall,
		NULL);

	VERTEX_3D * pVtx;   //頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-2000.0f, 2000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 2000.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(2000.0f, 2000.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-2000.0f, 1000.0f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(2000.0f, 1000.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
		{
			pVtx[nCntMesh].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		//頂点カラーの設定
		for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
		{
			pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;   //頂点データのポインタを９つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshwall->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshwall,
		NULL);

	WORD * pldx;	//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pldxBuffMeshwall->Lock(0, 0, (void**)&pldx, 0);

	//頂点番号データの設定
	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
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

		pldx += 14;   //頂点データのポインタを進める
	}

	//インデックスバッファをアンロックする
	g_pldxBuffMeshwall->Unlock();
}

//===============================================
//メッシュウォールの終了処理
//===============================================
void UninitMeshwall(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshwall != NULL)
	{
		g_pTextureMeshwall->Release();
		g_pTextureMeshwall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshwall != NULL)
	{
		g_pVtxBuffMeshwall->Release();
		g_pVtxBuffMeshwall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pldxBuffMeshwall != NULL)
	{
		g_pldxBuffMeshwall->Release();
		g_pldxBuffMeshwall = NULL;
	}
}

//===============================================
//メッシュウォールの更新処理
//===============================================
void UpdateMeshwall(void)
{

}

//===============================================
//メッシュウォールの描画処理
//===============================================
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
		D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
		D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(g_pldxBuffMeshwall);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshwall);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			9,
			0,
			12);
	}
}

//===============================================
//メッシュウォールの設定処理
//===============================================
void SetMeahwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	VERTEX_3D * pVtx;   //頂点情報へのポインタ
	int nCntMeshWall;
	int nCntMesh;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == false)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;
			g_aMeshWall[nCntMeshWall].rot = rot;
			g_aMeshWall[nCntMeshWall].nMeshwallType = type;
			g_aMeshWall[nCntMeshWall].bUse = true;

			GetWall(g_aMeshWall[0].pos + pVtx[0].pos, g_aMeshWall[0].pos + pVtx[8].pos, 0);

			//GetWall(D3DXVECTOR3(g_aMeshWall[nCntMeshWall].pos.x + sinf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[0].pos.x,
			//					g_aMeshWall[nCntMeshWall].pos.y,
			//					g_aMeshWall[nCntMeshWall].pos.z + sinf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[0].pos.z),
			//		D3DXVECTOR3(g_aMeshWall[nCntMeshWall].pos.x + cosf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[8].pos.x,
			//					g_aMeshWall[nCntMeshWall].pos.y,
			//					g_aMeshWall[nCntMeshWall].pos.z + cosf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[8].pos.z),
			//					nCntMeshWall);

			if (g_aMeshWall[nCntMeshWall].nMeshwallType == MESHWALLTYPE_NORMAL)
			{
				//頂点カラーの設定
				for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
				{
					pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

				break;
			}
			else if (g_aMeshWall[nCntMeshWall].nMeshwallType == MESHWALLTYPE_INVISIBLE)
			{
				//頂点カラーの設定
				for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
				{
					pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[5].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);

				break;
			}
		}
		pVtx += 9;   //頂点データのポインタを９つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshwall->Unlock();
}