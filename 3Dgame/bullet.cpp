//=========================================================
//
//3Dゲーム[bullet.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"bullet.h"
#include"shadow.h"
#include"explosion.h"
#include"meshwall.h"

//マクロ定義
#define MAX_BULLET		(128)	//弾の最大数
#define BULLET_SPEED	(10.0f)	//弾の速さ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//現在の位置
	D3DXVECTOR3 posOld;				//前回の位置
	D3DXVECTOR3 vecMove;			//移動ベクトル
	D3DXVECTOR3 vecToPos;			//pos0からvecMoveまで
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX g_mtxWorldBullet;	//ワールドマトリックス
	int g_nIdxBulletShadow;			//
	int nLife;						//寿命
	float fAngle;					//対角線の角度
	float fLength;					//対角線の長さ
	bool bUse;						//使用しているかどうか
}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報
D3DXVECTOR3 vecLine[MAX_MESHWALL];
D3DXVECTOR3 posWallS[MAX_MESHWALL];
D3DXVECTOR3 posWallE[MAX_MESHWALL];

//===============================================
//弾の初期化処理
//===============================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_3D *pVtx = 0;						//頂点情報へのポインタ
	int nCntBullet;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きを初期化（Z軸を使用）
		g_aBullet[nCntBullet].g_nIdxBulletShadow = -1;
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].fAngle = atan2f(6.0f, 6.0f);						//対角線の角度を算出する
		g_aBullet[nCntBullet].fLength = sqrtf(6.0f * 6.0f + 6.0f * 6.0f) *0.5f;	//対角線の長さを算出する
		g_aBullet[nCntBullet].bUse = false;										//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-6.0f, 6.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(6.0f, 6.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-6.0f, -6.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(6.0f, -6.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//弾の終了処理
//===============================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//===============================================
//弾の更新処理
//===============================================
void UpdateBullet(void)
{
	VERTEX_3D *pVtx = 0;   //頂点情報へのポインタ
	Bullet * pBullet = &g_aBullet[0];
	int nCntBullet;
	int nCntWall;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{//弾が使用されている

			//前回の情報を保存
			pBullet->posOld = pBullet->pos;

			//位置を更新
			pBullet->pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * BULLET_SPEED;
			pBullet->pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * BULLET_SPEED;

			//影の位置を設定
			SetPositionShadow(pBullet->g_nIdxBulletShadow, pBullet->pos, SHADOWTYPE_BULLET, true);

			pBullet->nLife--;

			for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
			{
				pBullet->vecToPos = pBullet->pos - posWallS[nCntWall];

				if ((vecLine[nCntWall].z * pBullet->vecToPos.x - vecLine[nCntWall].x * pBullet->vecToPos.z) < 0 
					|| pBullet->nLife == 0 && pBullet->bUse == true)
				{//寿命が尽きた
					//爆発の設定
					SetExplosion(pBullet->pos);
					pBullet->bUse = false;   //使用していない状態にする
					SetPositionShadow(pBullet->g_nIdxBulletShadow, pBullet->pos, SHADOWTYPE_BULLET, false);
				}
			}
		}
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//弾の描画処理
//===============================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_3D *pVtx = 0;						//頂点情報へのポインタ
	D3DXMATRIX mtxTrans;						//計算用マトリックス
	D3DXMATRIX mtxView;							//ビューマトリックス取得用
	int nCntBullet;

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].g_mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);

			//逆行列を求める
			g_aBullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
			g_aBullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
			g_aBullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, 
				g_aBullet[nCntBullet].pos.x, 
				g_aBullet[nCntBullet].pos.y, 
				g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].g_mtxWorldBullet, &g_aBullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].g_mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//===============================================
//弾の設定処理
//===============================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	VERTEX_3D *pVtx = 0;   //頂点情報へのポインタ
	int nCntBullet;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない

			g_aBullet[nCntBullet].bUse = true;   //使用している状態にする
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nLife = nLife;

			//影を設定
			g_aBullet[nCntBullet].g_nIdxBulletShadow = SetShadow();
			
			break;
		}
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//壁情報の取得
//===============================================
void GetWall(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, int nCntWall)
{
	posWallS[nCntWall] = pos0;
	posWallE[nCntWall] = pos1;
	vecLine[nCntWall] = posWallE[nCntWall] - posWallS[nCntWall];
}