//=========================================================
//
//3D�Q�[��[camera.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"input.h"
#include"camera.h"
#include"model.h"

//�}�N����`
#define MOVE_CAMERA			(2.0f)		//�J�����̓���
#define RAD_CAMERA			(60.0f)		//��{������̉�]�p�x
#define NANAME				(0.25f)		//�΂�
#define XMOVE				(0.5f)		//X�̈ړ�
#define PI_SLASH			(100.0f)	//IP�����鐔
#define LENGTH_CAMERA		(-400.0f)	//����
#define MOVEV_MINUS			(0.3f)		//���_�̈ړ��ʂ̌���
#define MOVER_MINUS			(0.2f)		//�����_�̈ړ��ʂ̌���
#define POSR_DEST			(-7.0f)		//�J�����̒����_�̏����O�ɐݒ�
#define CAMERA_ROT_SPEED	(0.02f)		//�J�������v���C���[�̔w��ɉ�荞�ނ܂ł̃X�s�[�h
#define CAMERA_ROT_MOVE		(70)		//�J�����̌������ς��^�C�~���O

//�O���[�o���ϐ�
Camera g_camera;			//�J�����̏��
int g_nCameraRotCounter;	//�J�����̌������ς��܂ł��J�E���g����

//===============================================
//�J�����̏���������
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
//�J�����̏I������
//===============================================
void UninitCamera(void)
{
	
}

//===============================================
//�J�����̍X�V����
//===============================================
void UpdateCamera(void)
{
	Model * pModel = GetModel();
	//g_fAngle = atan2f(radiusX, radiusZ);

	//�J�����ړ�
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//����ړ�
			g_camera.posV.z += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//�����ړ�
			g_camera.posV.z -= sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z -= sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else
		{//���ړ�
			g_camera.posV.x += sinf(-D3DX_PI * XMOVE) * MOVE_CAMERA;
			g_camera.posR.x += sinf(-D3DX_PI * XMOVE) * MOVE_CAMERA;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//�E��ړ�
			g_camera.posV.z -= sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z -= sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//�E���ړ�
			g_camera.posV.z += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.z += sinf(-D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posV.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * NANAME) * MOVE_CAMERA;
		}
		else
		{//�E�ړ�
			g_camera.posV.x += sinf(D3DX_PI * XMOVE) * MOVE_CAMERA;
			g_camera.posR.x += sinf(D3DX_PI * XMOVE) * MOVE_CAMERA;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ�i��ړ��j
		g_camera.posV.z -= cosf(D3DX_PI) * MOVE_CAMERA;
		g_camera.posR.z -= cosf(D3DX_PI) * MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ�i���ړ��j
		g_camera.posV.z -= cosf(D3DX_PI * ZERO) * MOVE_CAMERA;
		g_camera.posR.z -= cosf(D3DX_PI * ZERO) * MOVE_CAMERA;
	}

	//���_����
	if (GetKeyboardPress(DIK_Y) == true)
	{
		//��ړ�
		g_camera.posV.y += MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{
		//���ړ�
		g_camera.posV.y -= MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		//������
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
		//�E����
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

	//�����_����
	if (GetKeyboardPress(DIK_T) == true)
	{
		//��ړ�
		g_camera.posR.y += MOVE_CAMERA;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{
		//���ړ�
		g_camera.posR.y -= MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		//������
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
		//�E����
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

	//���_�ƒ����_�̃��Z�b�g
	if (GetKeyboardPress(DIK_R) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�J�����̒Ǐ]
	//g_camera.posR = pModel->pos;
	//�ړI�̎��_�E�����_��ݒ�
	g_camera.posRDest.x = pModel->pos.x + sinf(pModel->rot.y) * POSR_DEST;
	g_camera.posRDest.y = pModel->pos.y;
	g_camera.posRDest.z = pModel->pos.z + cosf(pModel->rot.y) * POSR_DEST;
	g_camera.posVDest.x = pModel->pos.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.y = pModel->pos.y;
	g_camera.posVDest.z = pModel->pos.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//�ړ��ʂ��X�V�i����������j
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * MOVEV_MINUS;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * MOVEV_MINUS;
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * MOVER_MINUS;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * MOVER_MINUS;

	////�����_�ƈꏏ�Ɏ��_��������
	//g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;

	if (pModel->bMove == false)
	{//�v���C���[�������Ȃ�����
		g_nCameraRotCounter--;
	}
	else if (pModel->bMove == true)
	{
		//�J�E���^�[�������l�ɖ߂�
		g_nCameraRotCounter = CAMERA_ROT_MOVE;
		pModel->bMove = false;
	}

	//�J�������v���C���[�̔w��Ɏ��肱�܂���
	if (g_nCameraRotCounter <= 0)
	{//�v���C���[�̓������~�܂���
		g_camera.rotDest.y = D3DX_PI + (ROT_CAMERA * pModel->rot.y);

		g_camera.rotDest.y -= g_camera.rot.y;	//�ړI�̌����܂ł̍���

		//�p�x�̒l�̕␳
		if (g_camera.rotDest.y > D3DX_PI)
		{
			g_camera.rotDest.y += -D3DX_PI * ROT_DIFF_PI;
		}
		else if (g_camera.rotDest.y < -D3DX_PI)
		{
			g_camera.rotDest.y += D3DX_PI * ROT_DIFF_PI;
		}

		g_camera.rot.y += g_camera.rotDest.y * CAMERA_ROT_SPEED;	//�p�x�̕␳

		//�p�x�̒l�̕␳
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
//�J�����̐ݒ菈��
//===============================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		6000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,
						&g_camera.posR,
						&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//===============================================
//�J�����̎擾
//===============================================
Camera * GetCamera(void)
{
	return &g_camera;
}