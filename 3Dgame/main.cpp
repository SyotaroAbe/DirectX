//=========================================================
//
//3Dゲーム[main.cpp]
//Author = 阿部翔大郎
//
//=========================================================

#include"main.h"
#include"input.h"
#include"camera.h"
#include"light.h"
#include"polygon.h"
#include"model.h"
#include"shadow.h"
#include"billboard.h"
#include"bullet.h"
#include"explosion.h"
#include"field.h"
#include"wall.h"
#include"meshfield.h"
#include"indexmeshfield.h"
#include"meshcylinder.h"
#include"meshwall.h"
#include"station.h"
#include"rock.h"
#include"corecrt_wstdio.h"
#include<stdio.h>

//マクロ定義
#define CLASS_NAME        "WindowClass"			//ウインドウクラスの名前
#define WINDOW_NAME       ""		//ウインドウの名前（キャプションに表示）

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UnInit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawCameraPos(void);
void DrawCameraRot(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;							//FPSカウンタ
int g_fCameraPosVz;								//カメラの位置（視点）
int g_fCameraPosRz;								//カメラの位置（注視点）
int g_fCameraRoty;								//カメラの向き
bool g_bDispDebug = false;						//デバッグ表示のON/OFF

//===============================================
//メイン関数
//===============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	Camera * pCamera = GetCamera();

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),               //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                       //ウインドウのスタイル
		WindowProc,                       //ウインドウプロシージャ
		0,                                //０にする（通常は使用しない）
		0,                                //０にする（通常は使用しない）
		hInstance,                        //インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),  //タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),      //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),       //クライアント領域の背景色
		NULL,                             //メニューバー
		CLASS_NAME,                       //ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION),  //ファイルのアイコン
	};

	HWND hWnd;   //ウインドウハンドル（識別子）
	MSG msg;     //メッセージを格納する変数
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };   //画面サイズの構造体
	DWORD dwCurrentTime;                                 //現在時刻
	DWORD dwExecLastTime;                                //最後に処理した時刻
	DWORD dwFrameCount;                                  //フレームカウント
	DWORD dwFPSLastTime;                                 //最後にFPSを計測した時刻

														 //ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,             //拡張ウインドウスタイル
		CLASS_NAME,                      //ウインドウクラスの名前
		WINDOW_NAME,                     //ウインドウの名前
		WS_OVERLAPPEDWINDOW,             //ウインドウスタイル
		CW_USEDEFAULT,                   //ウインドウの左上X座標
		CW_USEDEFAULT,                   //ウインドウの左上Y座標
		(rect.right - rect.left),        //ウインドウの幅
		(rect.bottom - rect.top),        //ウインドウの高さ
		NULL,                            //親ウインドウのハンドル
		NULL,                            //メニューハンドルまたは子ウインドウ
		hInstance,                       //インスタンスハンドル
		NULL);                           //ウインドウ制作データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;                //初期化する
	dwExecLastTime = timeGetTime();   //現在時刻を取得（保存）
	dwFrameCount = 0;                 //初期化する
	dwFPSLastTime = timeGetTime();    //現在時刻を取得（保存）

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);		//ウインドウの表示状態を設定
	UpdateWindow(hWnd);				//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);     //仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);      //ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();   //現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;   //FPSを計測した時刻を保存
				dwFrameCount = 0;                //フレームカウントをクリア

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//６０分の１秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻（現在時刻）を保存
				dwFrameCount++;						//フレームカウントを計算
				g_fCameraPosVz = pCamera->posV.z;	//カメラの位置（視点）を取得
				g_fCameraPosRz = pCamera->posR.z;	//カメラの位置（注視点）を取得
				g_fCameraRoty = pCamera->rot.y;		//カメラの向きを取得

				//更新処理
				Update();

				//描画処理
				Draw();
			}
		}
	}

	//終了処理
	UnInit();

	//分解能を戻す
	timeBeginPeriod(1);

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//===============================================
//ウインドウプロシージャ
//===============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;            //返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:   //ウインドウ破棄のメッセージ
					   //WM_QUIT メッセージを送る
		PostQuitMessage(1);
		break;
	case WM_KEYDOWN:   //キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:   //[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウインドウを破棄する（WM_DESTROYメッセージを送る）
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:   //閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウインドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;   //0を返さないと終了してしまう
		}
		break;
	case WM_LBUTTONDOWN:   //マウス左クリックのメッセージ
						   //対象ウインドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);    //既定の処理を繰り返す
}

//===============================================
//初期化設定
//===============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;          //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;   //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));                            //パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                         //ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                       //ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;                        //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                    //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                     //ダブルバッファの切り替え（映像パネルに同期）
	d3dpp.EnableAutoDepthStencil = TRUE;                          //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                    //デプスバッファとして１６bitを使う
	d3dpp.Windowed = bWindow;                                     //ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;   //リフレッシュモード
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;     //インターバル

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラースラートの誕生
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの誕生
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバッグ表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	////ポリゴンの初期化処理
	//InitPolygon();

	//メッシュシリンダーの初期化処理
	InitMeshcylinder();

	//メッシュフィールドの初期化処理
	InitIndexMeshfield();

	//ビルボードの初期化処理
	InitBillboard();

	//影の初期化処理
	InitShadow();

	//弾の初期化処理
	InitBullet();

	//モデルの初期化処理
	InitModel();

	//駅の初期化処理
	InitStation();

	//岩の初期化処理
	InitRock();

	//壁の初期化処理
	InitMeshwall();
	SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_NORMAL);
	//SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, 200.1f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_INVISIBLE);

	//爆発の初期化処理
	InitExplosion();

	//各種オブジェクトの初期化処理
	return S_OK;
}

//===============================================
//終了処理
//===============================================
void UnInit(void)
{//各種オブジェクトの終了処理

	//キーボードの終了処理
	UninitKeyboard();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	////ポリゴンの終了処理
	//UninitPolygon();

	//メッシュシリンダーの終了処理
	UninitMeshcylinder();

	//メッシュフィールドの終了処理
	UninitIndexMeshfield();

	//ビルボードの終了処理
	UninitBillboard();

	//影の終了処理
	UninitShadow();

	//弾の終了処理
	UninitBullet();

	//モデルの終了処理
	UninitModel();

	//駅の終了処理
	UninitStation();

	//岩の終了処理
	UninitRock();

	//壁の終了処理
	UninitMeshwall();

	//爆発の終了処理
	UninitExplosion();

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===============================================
//更新処理
//===============================================
void Update(void)
{//各種オブジェクトの更新処理

	//キーボードの更新処理
	UpdateKeyboard();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	////ポリゴンの更新処理
	//UpdatePolygon();

	//メッシュシリンダーの更新処理
	UpdateMeshcylinder();

	//メッシュフィールドの更新処理
	UpdateIndexMeshfield();

	//ビルボードの更新処理
	UpdateBillboard();

	//影の更新処理
	UpdateShadow();

	//弾の更新処理
	UpdateBullet();

	//モデルの更新処理
	UpdateModel();

	//駅の更新処理
	UpdateStation();

	//岩の更新処理
	UpdateRock();

	//壁の更新処理
	UpdateMeshwall();

	//爆発の更新処理
	UpdateExplosion();
}

//===============================================
//描画処理
//===============================================
void Draw(void)
{
	//画面クリア（バックバッファとＺバッファのクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		//各種オブジェクトの描画処理

		//カメラの設定処理
		SetCamera();

		////ポリゴンの描画処理
		//DrawPolygon();

		////メッシュシリンダーの描画処理
		//DrawMeshcylinder();

		//メッシュフィールドの描画処理
		DrawIndexMeshfield();

		//ビルボードの描画処理
		DrawBillboard();

		//影の描画処理
		DrawShadow();

		//弾の描画処理
		DrawBullet();

		//モデルの描画処理
		DrawModel();

		//駅の描画処理
		DrawStation();

		//岩の描画処理
		DrawRock();

		//壁の描画処理
		DrawMeshwall();

		//爆発の描画処理
		DrawExplosion();

#ifdef _DEBUG

		if (g_bDispDebug == true)
		{
			//FPSの表示
			DrawFPS();

			//DrawCameraPos();

			//DrawCameraRot();
		}

		if (GetKeyboardTrigger(DIK_F1) == true)
		{
			if (g_bDispDebug == true)
			{
				g_bDispDebug = false;
			}
			else if (g_bDispDebug == false)
			{
				g_bDispDebug = true;
			}
		}

#endif

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===============================================
//FPSの表示
//===============================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列の代入
	wsprintf(&aStr[0], "FPS：%d\n\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//カメラ距離の表示
//===============================================
void DrawCameraPos(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列の代入
	wsprintf(&aStr[0], "\n\n注視点と視点の距離：%d \n\n", g_fCameraPosRz - g_fCameraPosVz);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//カメラ向きの表示
//===============================================
void DrawCameraRot(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列の代入
	wsprintf(&aStr[0], "\n\n\n\n向き：%d \n\n", g_fCameraRoty);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//デバイスの取得
//===============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}