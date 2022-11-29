//=========================================================
//
//3Dゲーム[station.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"station.h"
#include"input.h"
#include"shadow.h"
#include"bullet.h"
#include"camera.h"
#include"meshwall.h"
#include"model.h"

//グローバル変数
Station g_station;											//駅の情報
LPDIRECT3DTEXTURE9 g_apTextureStation[MAX_TEXTURE] = {};	//テクスチャへのポインタ
LPD3DXMESH g_pMeshStation = NULL;							//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER g_pBuffMatStation = NULL;						//マテリアルへのポインタ
DWORD g_dwNumMatStation = 0;								//マテリアルの数
D3DXMATRIX g_mtxWorldStation;								//ワールドマトリックス
D3DXVECTOR3 g_vtxMinStation, g_vtxMaxStation;				//モデルの最大値・最小値

//===============================================
//駅の初期化処理
//===============================================
void InitStation(void)
{
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得

	//変数の初期化
	g_station.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.bMove = false;
	g_vtxMinStation = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxStation = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//Ｘファイルに読み込み
	D3DXLoadMeshFromX("data\\MODEL\\Station001SAPPORO.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatStation,
		NULL,
		&g_dwNumMatStation,
		&g_pMeshStation);

	//頂点数を取得
	nNumVtx = g_pMeshStation->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshStation->GetFVF());

	//頂点バッファをロック
	g_pMeshStation->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//全ての頂点を比較してモデルの最小値・最大値を抜き出す
		//最小値の比較
		if (vtx.x <= g_vtxMinStation.x)
		{
			g_vtxMinStation.x = vtx.x;
		}

		if (vtx.y <= g_vtxMinStation.y)
		{
			g_vtxMinStation.y = vtx.y;
		}

		if (vtx.z <= g_vtxMinStation.z)
		{
			g_vtxMinStation.z = vtx.z;
		}

		//最大値の比較
		if (vtx.x >= g_vtxMaxStation.x)
		{
			g_vtxMaxStation.x = vtx.x;
		}

		if (vtx.y >= g_vtxMaxStation.y)
		{
			g_vtxMaxStation.y = vtx.y;
		}

		if (vtx.z >= g_vtxMaxStation.z)
		{
			g_vtxMaxStation.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshStation->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatStation->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatStation; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureStation[nCntMat]);
		}
	}

	//影を設定
	g_station.g_nIdxShadow = SetShadow();
}

//===============================================
//駅の終了処理
//===============================================
void UninitStation(void)
{
	//メッシュの破棄
	if (g_pMeshStation != NULL)
	{
		g_pMeshStation->Release();
		g_pMeshStation = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatStation != NULL)
	{
		g_pBuffMatStation->Release();
		g_pBuffMatStation = NULL;
	}
}

//===============================================
//駅の更新処理
//===============================================
void UpdateStation(void)
{
	//プレイヤーがステージの外へ出ないようにする
	if (g_station.pos.z < WALL_SIZE && g_station.posOld.z >= WALL_SIZE)
	{
		g_station.pos.z = WALL_SIZE;
	}

	if (g_station.pos.z > -WALL_SIZE && g_station.posOld.z <= -WALL_SIZE)
	{
		g_station.pos.z = -WALL_SIZE;
	}

	if (g_station.pos.x < WALL_SIZE && g_station.posOld.x >= WALL_SIZE)
	{
		g_station.pos.x = WALL_SIZE;
	}

	if (g_station.pos.x > -WALL_SIZE && g_station.posOld.x <= -WALL_SIZE)
	{
		g_station.pos.x = -WALL_SIZE;
	}


	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ENTERキーが押された
		g_station.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_station.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	//影の位置を設定
	SetPositionShadow(g_station.g_nIdxShadow, g_station.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//駅の描画処理
//===============================================
void DrawStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldStation);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_station.rot.y, g_station.rot.x, g_station.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldStation, &g_mtxWorldStation, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_station.pos.x, g_station.pos.y, g_station.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldStation, &g_mtxWorldStation, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldStation);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatStation->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatStation; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureStation[nCntMat]);

		//モデル（パーツ）の描画
		g_pMeshStation->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===============================================
//駅の取得
//===============================================
Station * GetStation(void)
{
	return &g_station;
}