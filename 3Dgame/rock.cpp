//=========================================================
//
//3Dゲーム[rock.cpp]
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
#include"rock.h"

//グローバル変数
Rock g_rock;											//岩の情報
LPDIRECT3DTEXTURE9 g_apTextureRock[MAX_TEXTURE] = {};	//テクスチャへのポインタ
LPD3DXMESH g_pMeshRock = NULL;							//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER g_pBuffMatRock = NULL;						//マテリアルへのポインタ
DWORD g_dwNumMatRock = 0;								//マテリアルの数
D3DXMATRIX g_mtxWorldRock;								//ワールドマトリックス
D3DXVECTOR3 g_vtxMinRock, g_vtxMaxRock;					//モデルの最大値・最小値

//===============================================
//岩の初期化処理
//===============================================
void InitRock(void)
{
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得

	//変数の初期化
	g_rock.pos = D3DXVECTOR3(150.0f, -10.0f, 0.0f);
	g_rock.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rock.bMove = false;
	g_vtxMinRock = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxRock = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//Ｘファイルに読み込み
	D3DXLoadMeshFromX("data\\MODEL\\rock.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock,
		NULL,
		&g_dwNumMatRock,
		&g_pMeshRock);

	//頂点数を取得
	nNumVtx = g_pMeshRock->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshRock->GetFVF());

	//頂点バッファをロック
	g_pMeshRock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//全ての頂点を比較してモデルの最小値・最大値を抜き出す
		//最小値の比較
		if (vtx.x <= g_vtxMinRock.x)
		{
			g_vtxMinRock.x = vtx.x;
		}

		if (vtx.y <= g_vtxMinRock.y)
		{
			g_vtxMinRock.y = vtx.y;
		}

		if (vtx.z <= g_vtxMinRock.z)
		{
			g_vtxMinRock.z = vtx.z;
		}

		//最大値の比較
		if (vtx.x >= g_vtxMaxRock.x)
		{
			g_vtxMaxRock.x = vtx.x;
		}

		if (vtx.y >= g_vtxMaxRock.y)
		{
			g_vtxMaxRock.y = vtx.y;
		}

		if (vtx.z >= g_vtxMaxRock.z)
		{
			g_vtxMaxRock.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshRock->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatRock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureRock[nCntMat]);
		}
	}

	//影を設定
	g_rock.g_nIdxShadow = SetShadow();
}

//===============================================
//岩の終了処理
//===============================================
void UninitRock(void)
{
	//メッシュの破棄
	if (g_pMeshRock != NULL)
	{
		g_pMeshRock->Release();
		g_pMeshRock = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatRock != NULL)
	{
		g_pBuffMatRock->Release();
		g_pBuffMatRock = NULL;
	}
}

//===============================================
//岩の更新処理
//===============================================
void UpdateRock(void)
{
	//プレイヤーがステージの外へ出ないようにする
	if (g_rock.pos.z < WALL_SIZE && g_rock.posOld.z >= WALL_SIZE)
	{
		g_rock.pos.z = WALL_SIZE;
	}

	if (g_rock.pos.z > -WALL_SIZE && g_rock.posOld.z <= -WALL_SIZE)
	{
		g_rock.pos.z = -WALL_SIZE;
	}

	if (g_rock.pos.x < WALL_SIZE && g_rock.posOld.x >= WALL_SIZE)
	{
		g_rock.pos.x = WALL_SIZE;
	}

	if (g_rock.pos.x > -WALL_SIZE && g_rock.posOld.x <= -WALL_SIZE)
	{
		g_rock.pos.x = -WALL_SIZE;
	}


	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ENTERキーが押された
		g_rock.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_rock.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	//影の位置を設定
	SetPositionShadow(g_rock.g_nIdxShadow, g_rock.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//岩の描画処理
//===============================================
void DrawRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldRock);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rock.rot.y, g_rock.rot.x, g_rock.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldRock, &g_mtxWorldRock, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_rock.pos.x, g_rock.pos.y, g_rock.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldRock, &g_mtxWorldRock, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldRock);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatRock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureRock[nCntMat]);

		//モデル（パーツ）の描画
		g_pMeshRock->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===============================================
//岩の取得
//===============================================
Rock * GetRock(void)
{
	return &g_rock;
}