//=========================================================
//
//3D�Q�[��[meshwall.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"meshwall.h"
#include"bullet.h"
#include"model.h"
#include"camera.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshwall = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshwall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshwall = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_aMeshWall[MAX_MESHWALL];					//�ǂ̏��

//===============================================
//���b�V���E�H�[���̏���������
//===============================================
void InitMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾
	int nCntMeshWall;
	int nCntMesh;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshwall);

	//�ϐ��̏�����
	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshwall,
		NULL);

	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-2000.0f, 2000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 2000.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(2000.0f, 2000.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-2000.0f, 1000.0f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(2000.0f, 1000.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
		{
			pVtx[nCntMesh].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		//���_�J���[�̐ݒ�
		for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
		{
			pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;   //���_�f�[�^�̃|�C���^���X���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshwall,
		NULL);

	WORD * pldx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pldxBuffMeshwall->Lock(0, 0, (void**)&pldx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		pldx[0] = 3;
		pldx[1] = 0;
		pldx[2] = 4;
		pldx[3] = 1;
		pldx[4] = 5;
		pldx[5] = 2;
		pldx[6] = 2;
		pldx[7] = 6;
		pldx[8] = 6;
		pldx[9] = 3;
		pldx[10] = 7;
		pldx[11] = 4;
		pldx[12] = 8;
		pldx[13] = 5;

		pldx += 14;   //���_�f�[�^�̃|�C���^��i�߂�
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pldxBuffMeshwall->Unlock();
}

//===============================================
//���b�V���E�H�[���̏I������
//===============================================
void UninitMeshwall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshwall != NULL)
	{
		g_pTextureMeshwall->Release();
		g_pTextureMeshwall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshwall != NULL)
	{
		g_pVtxBuffMeshwall->Release();
		g_pVtxBuffMeshwall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pldxBuffMeshwall != NULL)
	{
		g_pldxBuffMeshwall->Release();
		g_pldxBuffMeshwall = NULL;
	}
}

//===============================================
//���b�V���E�H�[���̍X�V����
//===============================================
void UpdateMeshwall(void)
{

}

//===============================================
//���b�V���E�H�[���̕`�揈��
//===============================================
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
		D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
		D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorldMeshwall);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(g_pldxBuffMeshwall);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshwall);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			9,
			0,
			12);
	}
}

//===============================================
//���b�V���E�H�[���̐ݒ菈��
//===============================================
void SetMeahwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^
	int nCntMeshWall;
	int nCntMesh;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == false)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;
			g_aMeshWall[nCntMeshWall].rot = rot;
			g_aMeshWall[nCntMeshWall].nMeshwallType = type;
			g_aMeshWall[nCntMeshWall].bUse = true;

			GetWall(g_aMeshWall[0].pos + pVtx[0].pos, g_aMeshWall[0].pos + pVtx[8].pos, 0);

			//GetWall(D3DXVECTOR3(g_aMeshWall[nCntMeshWall].pos.x + sinf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[0].pos.x,
			//					g_aMeshWall[nCntMeshWall].pos.y,
			//					g_aMeshWall[nCntMeshWall].pos.z + sinf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[0].pos.z),
			//		D3DXVECTOR3(g_aMeshWall[nCntMeshWall].pos.x + cosf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[8].pos.x,
			//					g_aMeshWall[nCntMeshWall].pos.y,
			//					g_aMeshWall[nCntMeshWall].pos.z + cosf(g_aMeshWall[nCntMeshWall].rot.y + (ROT_CAMERA * pCamera->rot.y)) * pVtx[8].pos.z),
			//					nCntMeshWall);

			if (g_aMeshWall[nCntMeshWall].nMeshwallType == MESHWALLTYPE_NORMAL)
			{
				//���_�J���[�̐ݒ�
				for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
				{
					pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

				break;
			}
			else if (g_aMeshWall[nCntMeshWall].nMeshwallType == MESHWALLTYPE_INVISIBLE)
			{
				//���_�J���[�̐ݒ�
				for (nCntMesh = 0; nCntMesh < 9; nCntMesh++)
				{
					pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[5].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);

				break;
			}
		}
		pVtx += 9;   //���_�f�[�^�̃|�C���^���X���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();
}