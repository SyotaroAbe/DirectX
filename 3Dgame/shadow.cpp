//=========================================================
//
//3D�Q�[��[shadow.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"shadow.h"

//�}�N����`
#define MAX_SHADOW	(256)	//�e�̍ő吔

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX g_mtxWorldShadow;	//���[���h�}�g���b�N�X
	int nType;						//���
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Shadow;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;        //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;   //���_�o�b�t�@�ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];						//�e�̏��

//===============================================
//�e�̏���������
//===============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();    //�f�o�C�X�̎擾
	int nCntShadow;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//�ϐ��̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//===============================================
//�e�̏I������
//===============================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//===============================================
//�e�̍X�V����
//===============================================
void UpdateShadow(void)
{

}

//===============================================
//�e�̕`�揈��
//===============================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	int nCntShadow = -1;

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{//�e���g�p����Ă���

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].g_mtxWorldShadow);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].g_mtxWorldShadow, &g_aShadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].g_mtxWorldShadow, &g_aShadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].g_mtxWorldShadow);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===============================================
//�e�̐ݒ菈��
//===============================================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}

	return nCntShadow;
}

//===============================================
//�e�̈ʒu�ݒ菈��
//===============================================
void SetPositionShadow(int nTdxShadow, D3DXVECTOR3 pos, int type, bool bUse)
{
	VERTEX_3D * pVtx;   //���_���ւ̃|�C���^
	int nCntShadow;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (nCntShadow == nTdxShadow)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].nType = type;
			g_aShadow[nCntShadow].bUse = bUse;

			if (g_aShadow[nCntShadow].nType == SHADOWTYPE_PLAYER)
			{//�v���C���[�̉e
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
				pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
				pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
				pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
			}
			else if (g_aShadow[nCntShadow].nType == SHADOWTYPE_BULLET)
			{//�e�̉e
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
				pVtx[1].pos = D3DXVECTOR3(20.0f, 0.0f, 20.0f);
				pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
				pVtx[3].pos = D3DXVECTOR3(20.0f, 0.0f, -20.0f);
			}
			break;
		}
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}