//=========================================================
//
//3Dゲーム[camera.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"input.h"
#include"camera.h"
#include"model.h"

//マクロ定義
#define MOVE_CAMERA			(2.0f)		//カメラの動き
#define RAD_CAMERA			(60.0f)		//基本軸からの回転角度
#define NANAME				(0.25f)		//斜め
#define XMOVE				(0.5f)		//Xの移動
#define PI_SLASH			(100.0f)	//IPを割る数
#define LENGTH_CAMERA		(-400.0f)	//距離
#define MOVEV_MINUS			(0.3f)		//視点の移動量の減衰
#define MOVER_MINUS			(0.2f)		//注視点の移動量の減衰
#define POSR_DEST			(-7.0f)		//カメラの注視点の少し前に設定
#define CAMERA_ROT_SPEED	(0.02f)		//カメラがプレイヤーの背後に回り込むまでのスピード
#define CAMERA_ROT_MOVE		(70)		//カメラの向きが変わるタイミング

//グローバル変数
Camera g_camera;			//カメラの情報
int g_nCameraRotCounter;	//カメラの向きが変わるまでをカウントする

//===============================================
//カメラの初期化処理
//===============================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = LENGTH_CAMERA;
	g_nCameraRotCounter = CAMERA_ROT_MOVE;
}

//===============================================
//カメラの終了処理
//===============================================
void UninitCamera(void)
{
	
}

//===============================================
//カメラの更新処理
//===============================================
void UpdateCamera(void)
{
	Model * pModel = GetModel();
	//g_fAngle = atan2f(radiusX, radiusZ);

	//カメラ移動
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//左上移動
			g_camera.posV.z += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//左下移動
			g_camera.posV.z -= sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z -= sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else
		{//左移動
			g_camera.posV.x += sinf(-D3DX_PI * XMOVE) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * XMOVE) * MOVE_CAMERA;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//右上移動
			g_camera.posV.z -= sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z -= sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//右下移動
			g_camera.posV.z += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else
		{//右移動
			g_camera.posV.x += sinf(D3DX_PI * XMOVE) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * XMOVE) * MOVE_CAMERA;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された（上移動）
		g_camera.posV.z -= cosf(D3DX_PI) * MOVE_CAMERA;
		g_camera.posR.z -= cosf(D3DX_PI) * MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された（下移動）
		g_camera.posV.z -= cosf(D3DX_PI * ZERO) * MOVE_CAMERA;
		g_camera.posR.z -= cosf(D3DX_PI * ZERO) * MOVE_CAMERA;
	}

	//視点操作
	if (GetKeyboardPress(DIK_Y) == true)
	{
		//上移動
		g_camera.posV.y += MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{
		//下移動
		g_camera.posV.y -= MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		//左旋回
		g_camera.rot.y += D3DX_PI / PI_SLASH;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{
		//右旋回
		g_camera.rot.y -= D3DX_PI / PI_SLASH;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}

	//注視点操作
	if (GetKeyboardPress(DIK_T) == true)
	{
		//上移動
		g_camera.posR.y += MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{
		//下移動
		g_camera.posR.y -= MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		//左旋回
		g_camera.rot.y -= D3DX_PI / PI_SLASH;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{
		//右旋回
		g_camera.rot.y += D3DX_PI / PI_SLASH;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	}

	//視点と注視点のリセット
	if (GetKeyboardPress(DIK_R) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//カメラの追従
	//g_camera.posR = pModel->pos;
	//目的の視点・注視点を設定
	g_camera.posRDest.x = pModel->pos.x + sinf(pModel->rot.y) * POSR_DEST;
	g_camera.posRDest.y = pModel->pos.y;
	g_camera.posRDest.z = pModel->pos.z + cosf(pModel->rot.y) * POSR_DEST;
	g_camera.posVDest.x = pModel->pos.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.y = pModel->pos.y;
	g_camera.posVDest.z = pModel->pos.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//移動量を更新（減衰させる）
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * MOVEV_MINUS;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * MOVEV_MINUS;
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * MOVER_MINUS;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * MOVER_MINUS;

	////注視点と一緒に視点も動かす
	//g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;

	if (pModel->bMove == false)
	{//プレイヤーが動かなかった
		g_nCameraRotCounter--;
	}
	else if (pModel->bMove == true)
	{
		//カウンターを初期値に戻す
		g_nCameraRotCounter = CAMERA_ROT_MOVE;
		pModel->bMove = false;
	}

	//カメラをプレイヤーの背後に周りこませる
	if (g_nCameraRotCounter <= 0)
	{//プレイヤーの動きが止まった
		g_camera.rotDest.y = D3DX_PI + (ROT_CAMERA * pModel->rot.y);

		g_camera.rotDest.y -= g_camera.rot.y;	//目的の向きまでの差分

		//角度の値の補正
		if (g_camera.rotDest.y > D3DX_PI)
		{
			g_camera.rotDest.y += -D3DX_PI * ROT_DIFF_PI;
		}
		else if (g_camera.rotDest.y < -D3DX_PI)
		{
			g_camera.rotDest.y += D3DX_PI * ROT_DIFF_PI;
		}

		g_camera.rot.y += g_camera.rotDest.y * CAMERA_ROT_SPEED;	//角度の補正

		//角度の値の補正
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y += -D3DX_PI * ROT_DIFF_PI;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * ROT_DIFF_PI;
		}
	}
}

//===============================================
//カメラの設定処理
//===============================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		6000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,
						&g_camera.posR,
						&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//===============================================
//カメラの取得
//===============================================
Camera * GetCamera(void)
{
	return &g_camera;
}