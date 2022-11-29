//=========================================================
//
//3Dゲーム[model.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"model.h"
#include"input.h"
#include"shadow.h"
#include"bullet.h"
#include"camera.h"
#include"meshwall.h"

//マクロ定義
#define MODEL_MOVE			(0.4f)		//モデルの動くスピード
#define MOVE_MINUS			(0.07f)		//移動量の減衰
#define UP_LR_CAMERA_MOVE	(0.25f)		//斜め上に動く向き
#define DOWN_LR_CAMERA_MOVE	(0.75f)		//斜め下に動く向き
#define LR_CAMERA_MOVE		(0.5f)		//横に動く向き
#define UP_LR_CAMERA_ROT	(0.75f)		//斜め上に動くときの向き
#define DOWN_LR_CAMERA_ROT	(0.25f)		//斜め下に動くときの向き
#define LR_CAMERA_ROT		(0.5f)		//横に動くときの向き
#define DOWN_CAMERA_ROT		(1.0f)		//下に動くときの向き

//グローバル変数
Model g_model;											//モデルの情報
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_TEXTURE] = {};	//テクスチャへのポインタ
LPD3DXMESH g_pMeshModel = NULL;							//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;					//マテリアルへのポインタ
DWORD g_dwNumMatModel = 0;								//マテリアルの数
D3DXMATRIX g_mtxWorldModel;								//ワールドマトリックス
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;				//モデルの最大値・最小値
int g_nIdxShadow = -1;

//===============================================
//モデルの初期化処理
//===============================================
void InitModel(void)
{
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //デバイスの取得

	//変数の初期化
	g_model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.bMove = false;
	g_vtxMinModel = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxModel = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//Ｘファイルに読み込み
	D3DXLoadMeshFromX("data\\MODEL\\Stage_Illumination.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_dwNumMatModel,
						&g_pMeshModel);

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//全ての頂点を比較してモデルの最小値・最大値を抜き出す
		//最小値の比較
		if (vtx.x <= g_vtxMinModel.x)
		{
			g_vtxMinModel.x = vtx.x;
		}

		if (vtx.y <= g_vtxMinModel.y)
		{
			g_vtxMinModel.y = vtx.y;
		}

		if (vtx.z <= g_vtxMinModel.z)
		{
			g_vtxMinModel.z = vtx.z;
		}

		//最大値の比較
		if (vtx.x >= g_vtxMaxModel.x)
		{
			g_vtxMaxModel.x = vtx.x;
		}

		if (vtx.y >= g_vtxMaxModel.y)
		{
			g_vtxMaxModel.y = vtx.y;
		}

		if (vtx.z >= g_vtxMaxModel.z)
		{
			g_vtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}

	//影を設定
	g_nIdxShadow = SetShadow();
}

//===============================================
//モデルの終了処理
//===============================================
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//===============================================
//モデルの更新処理
//===============================================
void UpdateModel(void)
{
	Camera * pCamera = GetCamera();

	//前回の情報を保存
	g_model.posOld = g_model.pos;

	if (GetKeyboardPress(DIK_LEFT) == true)
	{//左キーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{//左上移動
			g_model.move.x += sinf(-D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * UP_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//左下移動
			g_model.move.x += sinf(-D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * DOWN_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else
		{//左移動
			g_model.move.x += sinf(-D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
			
		}
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//右キーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{//右上移動
			g_model.move.x += sinf(D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * UP_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//右下移動
			g_model.move.x += sinf(D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * DOWN_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else
		{//右移動
			g_model.move.x += sinf(D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//上キーが押された
		g_model.move.x += sinf(D3DX_PI * ZERO + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.move.z += cosf(D3DX_PI * ZERO + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.rotDest.y = D3DX_PI + (ROT_CAMERA * pCamera->rot.y);
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//下キーが押された
		g_model.move.x += sinf(D3DX_PI * DOWN_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.move.z += cosf(D3DX_PI * DOWN_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.rotDest.y = ZERO + (ROT_CAMERA * pCamera->rot.y);
		g_model.bMove = true;
	}

	g_model.fRotDiff = g_model.rotDest.y - g_model.rot.y;	//目的の向きまでの差分

	//角度の値の補正
	if (g_model.fRotDiff > D3DX_PI)
	{
		g_model.fRotDiff += -D3DX_PI * ROT_DIFF_PI;
	}
	else if (g_model.fRotDiff < -D3DX_PI)
	{
		g_model.fRotDiff += D3DX_PI * ROT_DIFF_PI;
	}

	g_model.rot.y += g_model.fRotDiff * ROT_CAMERA_DIFF;	//角度の補正

	//角度の値の補正
	if (g_model.rot.y > D3DX_PI)
	{
		g_model.rot.y += -D3DX_PI * ROT_DIFF_PI;
	}
	else if (g_model.rot.y < -D3DX_PI)
	{
		g_model.rot.y += D3DX_PI * ROT_DIFF_PI;
	}

	//位置を更新
	g_model.pos.x += g_model.move.x;
	g_model.pos.z += g_model.move.z;

	//移動量を更新（減衰させる）
	g_model.move.x += (ZERO - g_model.move.x) * MOVE_MINUS;
	g_model.move.z += (ZERO - g_model.move.z) * MOVE_MINUS;

	//プレイヤーがステージの外へ出ないようにする
	if (g_model.pos.z < WALL_SIZE && g_model.posOld.z >= WALL_SIZE)
	{
		g_model.pos.z = WALL_SIZE;
	}

	if (g_model.pos.z > -WALL_SIZE && g_model.posOld.z <= -WALL_SIZE)
	{
		g_model.pos.z = -WALL_SIZE;
	}

	if (g_model.pos.x < WALL_SIZE && g_model.posOld.x >= WALL_SIZE)
	{
		g_model.pos.x = WALL_SIZE;
	}

	if (g_model.pos.x > -WALL_SIZE && g_model.posOld.x <= -WALL_SIZE)
	{
		g_model.pos.x = -WALL_SIZE;
	}


	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ENTERキーが押された
		g_model.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_model.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACEキーが押された
		//弾の設定
		SetBullet(g_model.pos, g_model.rot, BULLET_LIFE);
	}

	//影の位置を設定
	SetPositionShadow(g_nIdxShadow, g_model.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//モデルの描画処理
//===============================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//モデル（パーツ）の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===============================================
//モデルの取得
//===============================================
Model * GetModel(void)
{
	return &g_model;
}
