//=========================================================
//
//3D�Q�[��[rock.cpp]
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
#include"rock.h"

//�O���[�o���ϐ�
Rock g_rock;											//��̏��
LPDIRECT3DTEXTURE9 g_apTextureRock[MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshRock = NULL;							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatRock = NULL;						//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatRock = 0;								//�}�e���A���̐�
D3DXMATRIX g_mtxWorldRock;								//���[���h�}�g���b�N�X
D3DXVECTOR3 g_vtxMinRock, g_vtxMaxRock;					//���f���̍ő�l�E�ŏ��l

//===============================================
//��̏���������
//===============================================
void InitRock(void)
{
	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾

	//�ϐ��̏�����
	g_rock.pos = D3DXVECTOR3(150.0f, -10.0f, 0.0f);
	g_rock.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rock.bMove = false;
	g_vtxMinRock = D3DXVECTOR3(MIN_VTX, MIN_VTX, MIN_VTX);
	g_vtxMaxRock = D3DXVECTOR3(MAX_VTX, MAX_VTX, MAX_VTX);

	//�w�t�@�C���ɓǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\rock.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock,
		NULL,
		&g_dwNumMatRock,
		&g_pMeshRock);

	//���_�����擾
	nNumVtx = g_pMeshRock->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshRock->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshRock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��
		//�ŏ��l�̔�r
		if (vtx.x <= g_vtxMinRock.x)
		{
			g_vtxMinRock.x = vtx.x;
		}

		if (vtx.y <= g_vtxMinRock.y)
		{
			g_vtxMinRock.y = vtx.y;
		}

		if (vtx.z <= g_vtxMinRock.z)
		{
			g_vtxMinRock.z = vtx.z;
		}

		//�ő�l�̔�r
		if (vtx.x >= g_vtxMaxRock.x)
		{
			g_vtxMaxRock.x = vtx.x;
		}

		if (vtx.y >= g_vtxMaxRock.y)
		{
			g_vtxMaxRock.y = vtx.y;
		}

		if (vtx.z >= g_vtxMaxRock.z)
		{
			g_vtxMaxRock.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshRock->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatRock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureRock[nCntMat]);
		}
	}

	//�e��ݒ�
	g_rock.g_nIdxShadow = SetShadow();
}

//===============================================
//��̏I������
//===============================================
void UninitRock(void)
{
	//���b�V���̔j��
	if (g_pMeshRock != NULL)
	{
		g_pMeshRock->Release();
		g_pMeshRock = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatRock != NULL)
	{
		g_pBuffMatRock->Release();
		g_pBuffMatRock = NULL;
	}
}

//===============================================
//��̍X�V����
//===============================================
void UpdateRock(void)
{
	//�v���C���[���X�e�[�W�̊O�֏o�Ȃ��悤�ɂ���
	if (g_rock.pos.z < WALL_SIZE && g_rock.posOld.z >= WALL_SIZE)
	{
		g_rock.pos.z = WALL_SIZE;
	}

	if (g_rock.pos.z > -WALL_SIZE && g_rock.posOld.z <= -WALL_SIZE)
	{
		g_rock.pos.z = -WALL_SIZE;
	}

	if (g_rock.pos.x < WALL_SIZE && g_rock.posOld.x >= WALL_SIZE)
	{
		g_rock.pos.x = WALL_SIZE;
	}

	if (g_rock.pos.x > -WALL_SIZE && g_rock.posOld.x <= -WALL_SIZE)
	{
		g_rock.pos.x = -WALL_SIZE;
	}


	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ENTER�L�[�������ꂽ
		g_rock.pos = D3DXVECTOR3(ZERO, ZERO, ZERO);
		g_rock.rot = D3DXVECTOR3(ZERO, ZERO, ZERO);
	}

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_rock.g_nIdxShadow, g_rock.pos, SHADOWTYPE_PLAYER, true);
}

//===============================================
//��̕`�揈��
//===============================================
void DrawRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldRock);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rock.rot.y, g_rock.rot.x, g_rock.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldRock, &g_mtxWorldRock, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_rock.pos.x, g_rock.pos.y, g_rock.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldRock, &g_mtxWorldRock, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldRock);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatRock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureRock[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		g_pMeshRock->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===============================================
//��̎擾
//===============================================
Rock * GetRock(void)
{
	return &g_rock;
}