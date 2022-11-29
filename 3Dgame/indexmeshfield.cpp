//=========================================================
//
//3D�Q�[��[indexmeshfield.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"indexmeshfield.h"

//�}�N����`
#define INDEXMESH_BLOCK_X	(2)			//���b�V���t�B�[���h�̃u���b�N���iX�j
#define INDEXMESH_SIZE_X	(200.0f)	//���b�V���t�B�[���h�̃T�C�Y�iX�j

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureIndexMeshfield = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffIndexMeshfield = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pldxBuffIndexMeshField = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posIndexMeshfield;							//�ʒu
D3DXVECTOR3 g_rotIndexMeshfield;							//����
D3DXMATRIX g_mtxWorldIndexMeshfield;						//���[���h�}�g���b�N�X
int g_nMaxMesh;												//�ő僁�b�V����

//===============================================
//���b�V���t�B�[���h�̏���������
//===============================================
void InitIndexMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾
	int nCntMesh;
	g_nMaxMesh = 9;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureIndexMeshfield);

	//�ϐ��̏�����
	g_posIndexMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotIndexMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nMaxMesh,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffIndexMeshfield,
		NULL);

	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffIndexMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	//for (nCntMesh = 0; nCntMesh < INDEXMESH_BLOCK_X; nCntMesh++)
	//{
	//	pVtx[nCntMesh].pos = D3DXVECTOR3(-200.0f + INDEXMESH_SIZE_X * nCntMesh, 0.0f, 200.0f);
	//}

	pVtx[0].pos = D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
	pVtx[2].pos = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);
	pVtx[3].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	pVtx[8].pos = D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);

	//�@���x�N�g���̐ݒ�
	for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	{
		pVtx[nCntMesh].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//���_�J���[�̐ݒ�
	for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	{
		pVtx[nCntMesh].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`�����W�̐ݒ�
	//for (nCntMesh = 0; nCntMesh < g_nMaxMesh; nCntMesh++)
	//{

	//}
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffIndexMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffIndexMeshField,
		NULL);

	WORD * pldx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pldxBuffIndexMeshField->Lock(0, 0, (void**)&pldx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
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

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pldxBuffIndexMeshField->Unlock();
}

//===============================================
//���b�V���t�B�[���h�̏I������
//===============================================
void UninitIndexMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureIndexMeshfield != NULL)
	{
		g_pTextureIndexMeshfield->Release();
		g_pTextureIndexMeshfield = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffIndexMeshfield != NULL)
	{
		g_pVtxBuffIndexMeshfield->Release();
		g_pVtxBuffIndexMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pldxBuffIndexMeshField != NULL)
	{
		g_pldxBuffIndexMeshField->Release();
		g_pldxBuffIndexMeshField = NULL;
	}
}

//===============================================
//���b�V���t�B�[���h�̍X�V����
//===============================================
void UpdateIndexMeshfield(void)
{

}

//===============================================
//���b�V���t�B�[���h�̕`�揈��
//===============================================
void DrawIndexMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldIndexMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotIndexMeshfield.y, g_rotIndexMeshfield.x, g_rotIndexMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldIndexMeshfield, &g_mtxWorldIndexMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posIndexMeshfield.x, g_posIndexMeshfield.y, g_posIndexMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldIndexMeshfield, &g_mtxWorldIndexMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldIndexMeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffIndexMeshfield, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pldxBuffIndexMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureIndexMeshfield);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 
		0,
		9,
		0,
		12);
}
