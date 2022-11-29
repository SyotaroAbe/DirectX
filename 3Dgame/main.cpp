//=========================================================
//
//3D�Q�[��[main.cpp]
//Author = �����đ�Y
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

//�}�N����`
#define CLASS_NAME        "WindowClass"			//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME       ""		//�E�C���h�E�̖��O�i�L���v�V�����ɕ\���j

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UnInit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawCameraPos(void);
void DrawCameraRot(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;							//FPS�J�E���^
int g_fCameraPosVz;								//�J�����̈ʒu�i���_�j
int g_fCameraPosRz;								//�J�����̈ʒu�i�����_�j
int g_fCameraRoty;								//�J�����̌���
bool g_bDispDebug = false;						//�f�o�b�O�\����ON/OFF

//===============================================
//���C���֐�
//===============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	Camera * pCamera = GetCamera();

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),               //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                       //�E�C���h�E�̃X�^�C��
		WindowProc,                       //�E�C���h�E�v���V�[�W��
		0,                                //�O�ɂ���i�ʏ�͎g�p���Ȃ��j
		0,                                //�O�ɂ���i�ʏ�͎g�p���Ȃ��j
		hInstance,                        //�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),  //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),      //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),       //�N���C�A���g�̈�̔w�i�F
		NULL,                             //���j���[�o�[
		CLASS_NAME,                       //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION),  //�t�@�C���̃A�C�R��
	};

	HWND hWnd;   //�E�C���h�E�n���h���i���ʎq�j
	MSG msg;     //���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };   //��ʃT�C�Y�̍\����
	DWORD dwCurrentTime;                                 //���ݎ���
	DWORD dwExecLastTime;                                //�Ō�ɏ�����������
	DWORD dwFrameCount;                                  //�t���[���J�E���g
	DWORD dwFPSLastTime;                                 //�Ō��FPS���v����������

														 //�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,             //�g���E�C���h�E�X�^�C��
		CLASS_NAME,                      //�E�C���h�E�N���X�̖��O
		WINDOW_NAME,                     //�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,             //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,                   //�E�C���h�E�̍���X���W
		CW_USEDEFAULT,                   //�E�C���h�E�̍���Y���W
		(rect.right - rect.left),        //�E�C���h�E�̕�
		(rect.bottom - rect.top),        //�E�C���h�E�̍���
		NULL,                            //�e�E�C���h�E�̃n���h��
		NULL,                            //���j���[�n���h���܂��͎q�E�C���h�E
		hInstance,                       //�C���X�^���X�n���h��
		NULL);                           //�E�C���h�E����f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;                //����������
	dwExecLastTime = timeGetTime();   //���ݎ������擾�i�ۑ��j
	dwFrameCount = 0;                 //����������
	dwFPSLastTime = timeGetTime();    //���ݎ������擾�i�ۑ��j

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);     //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);      //�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();   //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;   //FPS���v������������ۑ�
				dwFrameCount = 0;                //�t���[���J�E���g���N���A

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//�U�O���̂P�b�o��
				dwExecLastTime = dwCurrentTime;		//�����J�n�̎����i���ݎ����j��ۑ�
				dwFrameCount++;						//�t���[���J�E���g���v�Z
				g_fCameraPosVz = pCamera->posV.z;	//�J�����̈ʒu�i���_�j���擾
				g_fCameraPosRz = pCamera->posR.z;	//�J�����̈ʒu�i�����_�j���擾
				g_fCameraRoty = pCamera->rot.y;		//�J�����̌������擾

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	UnInit();

	//����\��߂�
	timeBeginPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//===============================================
//�E�C���h�E�v���V�[�W��
//===============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;            //�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:   //�E�C���h�E�j���̃��b�Z�[�W
					   //WM_QUIT ���b�Z�[�W�𑗂�
		PostQuitMessage(1);
		break;
	case WM_KEYDOWN:   //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:   //[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�C���h�E��j������iWM_DESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:   //����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�C���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;   //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	case WM_LBUTTONDOWN:   //�}�E�X���N���b�N�̃��b�Z�[�W
						   //�ΏۃE�C���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);    //����̏������J��Ԃ�
}

//===============================================
//�������ݒ�
//===============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;          //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;   //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                            //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                         //�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                       //�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;                        //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                    //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                     //�_�u���o�b�t�@�̐؂�ւ��i�f���p�l���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;                          //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                    //�f�v�X�o�b�t�@�Ƃ��ĂP�Ubit���g��
	d3dpp.Windowed = bWindow;                                     //�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;   //���t���b�V�����[�h
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;     //�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X���[�g�̒a��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̒a��
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	////�|���S���̏���������
	//InitPolygon();

	//���b�V���V�����_�[�̏���������
	InitMeshcylinder();

	//���b�V���t�B�[���h�̏���������
	InitIndexMeshfield();

	//�r���{�[�h�̏���������
	InitBillboard();

	//�e�̏���������
	InitShadow();

	//�e�̏���������
	InitBullet();

	//���f���̏���������
	InitModel();

	//�w�̏���������
	InitStation();

	//��̏���������
	InitRock();

	//�ǂ̏���������
	InitMeshwall();
	SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), WALLTYPE_NORMAL);
	SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_NORMAL);
	//SetMeahwall(D3DXVECTOR3(0.0f, 0.0f, 200.1f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_INVISIBLE);

	//�����̏���������
	InitExplosion();

	//�e��I�u�W�F�N�g�̏���������
	return S_OK;
}

//===============================================
//�I������
//===============================================
void UnInit(void)
{//�e��I�u�W�F�N�g�̏I������

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	////�|���S���̏I������
	//UninitPolygon();

	//���b�V���V�����_�[�̏I������
	UninitMeshcylinder();

	//���b�V���t�B�[���h�̏I������
	UninitIndexMeshfield();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�e�̏I������
	UninitShadow();

	//�e�̏I������
	UninitBullet();

	//���f���̏I������
	UninitModel();

	//�w�̏I������
	UninitStation();

	//��̏I������
	UninitRock();

	//�ǂ̏I������
	UninitMeshwall();

	//�����̏I������
	UninitExplosion();

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===============================================
//�X�V����
//===============================================
void Update(void)
{//�e��I�u�W�F�N�g�̍X�V����

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	////�|���S���̍X�V����
	//UpdatePolygon();

	//���b�V���V�����_�[�̍X�V����
	UpdateMeshcylinder();

	//���b�V���t�B�[���h�̍X�V����
	UpdateIndexMeshfield();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//�e�̍X�V����
	UpdateShadow();

	//�e�̍X�V����
	UpdateBullet();

	//���f���̍X�V����
	UpdateModel();

	//�w�̍X�V����
	UpdateStation();

	//��̍X�V����
	UpdateRock();

	//�ǂ̍X�V����
	UpdateMeshwall();

	//�����̍X�V����
	UpdateExplosion();
}

//===============================================
//�`�揈��
//===============================================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@�Ƃy�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		//�e��I�u�W�F�N�g�̕`�揈��

		//�J�����̐ݒ菈��
		SetCamera();

		////�|���S���̕`�揈��
		//DrawPolygon();

		////���b�V���V�����_�[�̕`�揈��
		//DrawMeshcylinder();

		//���b�V���t�B�[���h�̕`�揈��
		DrawIndexMeshfield();

		//�r���{�[�h�̕`�揈��
		DrawBillboard();

		//�e�̕`�揈��
		DrawShadow();

		//�e�̕`�揈��
		DrawBullet();

		//���f���̕`�揈��
		DrawModel();

		//�w�̕`�揈��
		DrawStation();

		//��̕`�揈��
		DrawRock();

		//�ǂ̕`�揈��
		DrawMeshwall();

		//�����̕`�揈��
		DrawExplosion();

#ifdef _DEBUG

		if (g_bDispDebug == true)
		{
			//FPS�̕\��
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

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===============================================
//FPS�̕\��
//===============================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������̑��
	wsprintf(&aStr[0], "FPS�F%d\n\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//�J���������̕\��
//===============================================
void DrawCameraPos(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������̑��
	wsprintf(&aStr[0], "\n\n�����_�Ǝ��_�̋����F%d \n\n", g_fCameraPosRz - g_fCameraPosVz);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//�J���������̕\��
//===============================================
void DrawCameraRot(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������̑��
	wsprintf(&aStr[0], "\n\n\n\n�����F%d \n\n", g_fCameraRoty);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//===============================================
//�f�o�C�X�̎擾
//===============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}