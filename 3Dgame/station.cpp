//=========================================================
//
//3D�Q�[��[station.cpp]
//Author = �����đ�Y
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

//�O���[�o���ϐ�
Station g_station;											//�w�̏��
LPDIRECT3DTEXTURE9 g_apTextureStation[MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshStation = NULL;							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatStation = NULL;						//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatStation = 0;								//�}�e���A���̐�
D3DXMATRIX g_mtxWorldStation;								//���[���h�}�g���b�N�X
D3DXVECTOR3 g_vtxMinStation, g_vtxMaxStation;				//���f���̍ő�l�E�ŏ��l

//===============================================
//�w�̏���������
//===============================================
void InitStation(void)
{
	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾

	//�ϐ��̏�����
	g_station.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_station.bMove = false;
	g_vtxMinStation = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxStation = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//�w�t�@�C���ɓǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Station001SAPPORO.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatStation,
		NULL,
		&g_dwNumMatStation,
		&g_pMeshStation);

	//���_�����擾
	nNumVtx = g_pMeshStation->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshStation->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshStation->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��
		//�ŏ��l�̔�r
		if (vtx.x <= g_vtxMinStation.x)
		{
			g_vtxMinStation.x = vtx.x;
		}

		if (vtx.y <= g_vtxMinStation.y)
		{
			g_vtxMinStation.y = vtx.y;
		}

		if (vtx.z <= g_vtxMinStation.z)
		{
			g_vtxMinStation.z = vtx.z;
		}

		//�ő�l�̔�r
		if (vtx.x >= g_vtxMaxStation.x)
		{
			g_vtxMaxStation.x = vtx.x;
		}

		if (vtx.y >= g_vtxMaxStation.y)
		{
			g_vtxMaxStation.y = vtx.y;
		}

		if (vtx.z >= g_vtxMaxStation.z)
		{
			g_vtxMaxStation.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshStation->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatStation->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatStation; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureStation[nCntMat]);
		}
	}

	//�e��ݒ�
	g_station.g_nIdxShadow = SetShadow();
}

//===============================================
//�w�̏I������
//===============================================
void UninitStation(void)
{
	//���b�V���̔j��
	if (g_pMeshStation != NULL)
	{
		g_pMeshStation->Release();
		g_pMeshStation = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatStation != NULL)
	{
		g_pBuffMatStation->Release();
		g_pBuffMatStation = NULL;
	}
}

//===============================================
//�w�̍X�V����
//===============================================
void UpdateStation(void)
{
	//�v���C���[���X�e�[�W�̊O�֏o�Ȃ��悤�ɂ���
	if (g_station.pos.z < WALL_SIZE && g_station.posOld.z >= WALL_SIZE)
	{
		g_station.pos.z = WALL_SIZE;
	}

	if (g_station.pos.z > -WALL_SIZE && g_station.posOld.z <= -WALL_SIZE)
	{
		g_station.pos.z = -WALL_SIZE;
	}

	if (g_station.pos.x < WALL_SIZE && g_station.posOld.x >= WALL_SIZE)
	{
		g_station.pos.x = WALL_SIZE;
	}

	if (g_station.pos.x > -WALL_SIZE && g_station.posOld.x <= -WALL_SIZE)
	{
		g_station.pos.x = -WALL_SIZE;
	}


	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ENTER�L�[�������ꂽ
		g_station.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_station.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_station.g_nIdxShadow, g_station.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//�w�̕`�揈��
//===============================================
void DrawStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldStation);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_station.rot.y, g_station.rot.x, g_station.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldStation, &g_mtxWorldStation, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_station.pos.x, g_station.pos.y, g_station.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldStation, &g_mtxWorldStation, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldStation);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatStation->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatStation; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureStation[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		g_pMeshStation->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===============================================
//�w�̎擾
//===============================================
Station * GetStation(void)
{
	return &g_station;
}