//=========================================================
//
//3D�Q�[��[wall.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"wall.h"

//�}�N����`
#define MAX_WALL	(2)		//�ő�ǐ�

//�Ǎ\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	int g_nWallType;			//�^�C�v
	D3DXMATRIX g_mtxWorldWall;	//���[���h�}�g���b�N�X
}Wall;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Wall g_aWall[MAX_WALL];							//�ǂ̏��

//===============================================
//�ǂ̏���������
//===============================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   //�f�o�C�X�̎擾
	int nCntWall;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	//�ϐ��̏�����
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-200.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//===============================================
//�ǂ̏I������
//===============================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//===============================================
//�ǂ̍X�V����
//===============================================
void UpdateWall(void)
{

}

//===============================================
//�ǂ̕`�揈��
//===============================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[nCntWall].g_mtxWorldWall);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorldWall, &g_aWall[nCntWall].g_mtxWorldWall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorldWall, &g_aWall[nCntWall].g_mtxWorldWall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].g_mtxWorldWall);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

//===============================================
//�ǂ̐ݒ菈��
//===============================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^
	int nCntWall;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = pos;
		g_aWall[nCntWall].rot = rot;
		g_aWall[nCntWall].g_nWallType = type;

		if (g_aWall[nCntWall].g_nWallType == WALLTYPE_NORMAL)
		{

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if (g_aWall[nCntWall].g_nWallType == WALLTYPE_INVISIBLE)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		break;
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}