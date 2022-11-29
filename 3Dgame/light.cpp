//=========================================================
//
//3Dゲーム[light.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"light.h"

//マクロ定義
#define MAX_LGHT	(3)	//ライトの数

//グローバル変数
D3DLIGHT9 g_light[MAX_LGHT];	//ライトの情報

//===============================================
//ライトの初期化処理
//===============================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir;							//設定用方向ベクトル
	int nCntLight;

	for (nCntLight = 0; nCntLight < MAX_LGHT; nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	}
		//ライトの方向を設定
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化する
		g_light[0].Direction = vecDir;
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化する
		g_light[1].Direction = vecDir;
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化する
		g_light[2].Direction = vecDir;

	for (nCntLight = 0; nCntLight < MAX_LGHT; nCntLight++)
	{
		//ライトを設定する
		pDevice->SetLight(0, &g_light[nCntLight]);
	}

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//===============================================
//ライトの終了処理
//===============================================
void UninitLight(void)
{
	
}

//===============================================
//ライトの更新処理
//===============================================
void UpdateLight(void)
{

}