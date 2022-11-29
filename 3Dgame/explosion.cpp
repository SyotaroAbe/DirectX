//=========================================================
//
//3Dゲーム[explosion.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"

//マクロ定義
#define MAX_EXPLOSION   (128)   //爆発の最大数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXMATRIX g_mtxWorldBullet;	//ワールドマトリックス
	int nCounterAnimExplosion;		//アニメーションカウンター
	int nPatternAnimExplosion;		//アニメーションパターンNo.
	bool bUse;						//使用しているかどうか
}Explosion;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;        //DirectInputオブジェクトへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;   //入力デバイス（キーボード）へのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];                //爆発の情報

//===============================================
//爆発の初期化処理
//===============================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_3D *pVtx = 0;						//頂点情報へのポインタ
	int nCntExplosion;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(6000.0f, 375.0f, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;   //使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-16.0f, 16.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-16.0f, -16.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(16.0f, -16.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;   //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//===============================================
//爆発の終了処理
//===============================================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//===============================================
//爆発の更新処理
//===============================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_3D *pVtx = 0;   //頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている

			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;   //カウンターを加算

			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % 5) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;   //カウンターを初期値に戻す
				g_aExplosion[nCntExplosion].nPatternAnimExplosion++;

				//頂点カラーの更新
				pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));

				//テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnimExplosion  > 7)
				{//総パターン数を超えた
					g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;

					g_aExplosion[nCntExplosion].bUse = false;   //使用していない状態にする
				}
			}
		}
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//===============================================
//爆発の描画処理
//===============================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_3D *pVtx = 0;						//頂点情報へのポインタ
	D3DXMATRIX mtxTrans;						//計算用マトリックス
	D3DXMATRIX mtxView;							//ビューマトリックス取得用
	int nCntExplosion;

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].g_mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aExplosion[nCntExplosion].g_mtxWorldBullet, NULL, &mtxView);

			//逆行列を求める
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._41 = 0.0f;
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._42 = 0.0f;
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aExplosion[nCntExplosion].pos.x,
				g_aExplosion[nCntExplosion].pos.y,
				g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].g_mtxWorldBullet,
				&g_aExplosion[nCntExplosion].g_mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].g_mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
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
//爆発の設定処理
//===============================================
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCntExplosion;
	VERTEX_3D *pVtx = 0;   //頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない
			g_aExplosion[nCntExplosion].bUse = true;   //使用している状態にする
			g_aExplosion[nCntExplosion].pos = pos;

			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;   //カウンターをリセット


			break;
		}
		pVtx += 4;   //頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}