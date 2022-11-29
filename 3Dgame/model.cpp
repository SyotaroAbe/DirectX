//=========================================================
//
//3D�Q�[��[model.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"model.h"
#include"input.h"
#include"shadow.h"
#include"bullet.h"
#include"camera.h"
#include"meshwall.h"

//�}�N����`
#define MODEL_MOVE			(0.4f)		//���f���̓����X�s�[�h
#define MOVE_MINUS			(0.07f)		//�ړ��ʂ̌���
#define UP_LR_CAMERA_MOVE	(0.25f)		//�΂ߏ�ɓ�������
#define DOWN_LR_CAMERA_MOVE	(0.75f)		//�΂߉��ɓ�������
#define LR_CAMERA_MOVE		(0.5f)		//���ɓ�������
#define UP_LR_CAMERA_ROT	(0.75f)		//�΂ߏ�ɓ����Ƃ��̌���
#define DOWN_LR_CAMERA_ROT	(0.25f)		//�΂߉��ɓ����Ƃ��̌���
#define LR_CAMERA_ROT		(0.5f)		//���ɓ����Ƃ��̌���
#define DOWN_CAMERA_ROT		(1.0f)		//���ɓ����Ƃ��̌���

//�O���[�o���ϐ�
Model g_model;											//���f���̏��
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshModel = NULL;							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;					//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatModel = 0;								//�}�e���A���̐�
D3DXMATRIX g_mtxWorldModel;								//���[���h�}�g���b�N�X
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;				//���f���̍ő�l�E�ŏ��l
int g_nIdxShadow = -1;

//===============================================
//���f���̏���������
//===============================================
void InitModel(void)
{
	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾

	//�ϐ��̏�����
	g_model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model.bMove = false;
	g_vtxMinModel = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxModel = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//�w�t�@�C���ɓǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Stage_Illumination.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_dwNumMatModel,
						&g_pMeshModel);

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��
		//�ŏ��l�̔�r
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

		//�ő�l�̔�r
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

		pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}

	//�e��ݒ�
	g_nIdxShadow = SetShadow();
}

//===============================================
//���f���̏I������
//===============================================
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//===============================================
//���f���̍X�V����
//===============================================
void UpdateModel(void)
{
	Camera * pCamera = GetCamera();

	//�O��̏���ۑ�
	g_model.posOld = g_model.pos;

	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{//����ړ�
			g_model.move.x += sinf(-D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * UP_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//�����ړ�
			g_model.move.x += sinf(-D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * DOWN_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else
		{//���ړ�
			g_model.move.x += sinf(-D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(-D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = D3DX_PI * LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
			
		}
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//�E�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{//�E��ړ�
			g_model.move.x += sinf(D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * UP_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * UP_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//�E���ړ�
			g_model.move.x += sinf(D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * DOWN_LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * DOWN_LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		else
		{//�E�ړ�
			g_model.move.x += sinf(D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.move.z += cosf(D3DX_PI * LR_CAMERA_MOVE + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
			g_model.rotDest.y = -D3DX_PI * LR_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y);
		}
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//��L�[�������ꂽ
		g_model.move.x += sinf(D3DX_PI * ZERO + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.move.z += cosf(D3DX_PI * ZERO + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.rotDest.y = D3DX_PI + (ROT_CAMERA * pCamera->rot.y);
		g_model.bMove = true;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//���L�[�������ꂽ
		g_model.move.x += sinf(D3DX_PI * DOWN_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.move.z += cosf(D3DX_PI * DOWN_CAMERA_ROT + (ROT_CAMERA * pCamera->rot.y)) * MODEL_MOVE;
		g_model.rotDest.y = ZERO + (ROT_CAMERA * pCamera->rot.y);
		g_model.bMove = true;
	}

	g_model.fRotDiff = g_model.rotDest.y - g_model.rot.y;	//�ړI�̌����܂ł̍���

	//�p�x�̒l�̕␳
	if (g_model.fRotDiff > D3DX_PI)
	{
		g_model.fRotDiff += -D3DX_PI * ROT_DIFF_PI;
	}
	else if (g_model.fRotDiff < -D3DX_PI)
	{
		g_model.fRotDiff += D3DX_PI * ROT_DIFF_PI;
	}

	g_model.rot.y += g_model.fRotDiff * ROT_CAMERA_DIFF;	//�p�x�̕␳

	//�p�x�̒l�̕␳
	if (g_model.rot.y > D3DX_PI)
	{
		g_model.rot.y += -D3DX_PI * ROT_DIFF_PI;
	}
	else if (g_model.rot.y < -D3DX_PI)
	{
		g_model.rot.y += D3DX_PI * ROT_DIFF_PI;
	}

	//�ʒu���X�V
	g_model.pos.x += g_model.move.x;
	g_model.pos.z += g_model.move.z;

	//�ړ��ʂ��X�V�i����������j
	g_model.move.x += (ZERO - g_model.move.x) * MOVE_MINUS;
	g_model.move.z += (ZERO - g_model.move.z) * MOVE_MINUS;

	//�v���C���[���X�e�[�W�̊O�֏o�Ȃ��悤�ɂ���
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
	{//ENTER�L�[�������ꂽ
		g_model.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_model.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACE�L�[�������ꂽ
		//�e�̐ݒ�
		SetBullet(g_model.pos, g_model.rot, BULLET_LIFE);
	}

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_nIdxShadow, g_model.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//���f���̕`�揈��
//===============================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===============================================
//���f���̎擾
//===============================================
Model * GetModel(void)
{
	return &g_model;
}
