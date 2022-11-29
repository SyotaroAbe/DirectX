//=========================================================
//
//3D�Q�[��[bullet.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"bullet.h"
#include"shadow.h"
#include"explosion.h"
#include"meshwall.h"

//�}�N����`
#define MAX_BULLET		(128)	//�e�̍ő吔
#define BULLET_SPEED	(10.0f)	//�e�̑���

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//���݂̈ʒu
	D3DXVECTOR3 posOld;				//�O��̈ʒu
	D3DXVECTOR3 vecMove;			//�ړ��x�N�g��
	D3DXVECTOR3 vecToPos;			//pos0����vecMove�܂�
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX g_mtxWorldBullet;	//���[���h�}�g���b�N�X
	int g_nIdxBulletShadow;			//
	int nLife;						//����
	float fAngle;					//�Ίp���̊p�x
	float fLength;					//�Ίp���̒���
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��
D3DXVECTOR3 vecLine[MAX_MESHWALL];
D3DXVECTOR3 posWallS[MAX_MESHWALL];
D3DXVECTOR3 posWallE[MAX_MESHWALL];

//===============================================
//�e�̏���������
//===============================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_3D *pVtx = 0;						//���_���ւ̃|�C���^
	int nCntBullet;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�������������iZ�����g�p�j
		g_aBullet[nCntBullet].g_nIdxBulletShadow = -1;
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].fAngle = atan2f(6.0f, 6.0f);						//�Ίp���̊p�x���Z�o����
		g_aBullet[nCntBullet].fLength = sqrtf(6.0f * 6.0f + 6.0f * 6.0f) *0.5f;	//�Ίp���̒������Z�o����
		g_aBullet[nCntBullet].bUse = false;										//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-6.0f, 6.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(6.0f, 6.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-6.0f, -6.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(6.0f, -6.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//�e�̏I������
//===============================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//===============================================
//�e�̍X�V����
//===============================================
void UpdateBullet(void)
{
	VERTEX_3D *pVtx = 0;   //���_���ւ̃|�C���^
	Bullet * pBullet = &g_aBullet[0];
	int nCntBullet;
	int nCntWall;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{//�e���g�p����Ă���

			//�O��̏���ۑ�
			pBullet->posOld = pBullet->pos;

			//�ʒu���X�V
			pBullet->pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * BULLET_SPEED;
			pBullet->pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * BULLET_SPEED;

			//�e�̈ʒu��ݒ�
			SetPositionShadow(pBullet->g_nIdxBulletShadow, pBullet->pos, SHADOWTYPE_BULLET, true);

			pBullet->nLife--;

			for (nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
			{
				pBullet->vecToPos = pBullet->pos - posWallS[nCntWall];

				if ((vecLine[nCntWall].z * pBullet->vecToPos.x - vecLine[nCntWall].x * pBullet->vecToPos.z) < 0 
					|| pBullet->nLife == 0 && pBullet->bUse == true)
				{//�������s����
					//�����̐ݒ�
					SetExplosion(pBullet->pos);
					pBullet->bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���
					SetPositionShadow(pBullet->g_nIdxBulletShadow, pBullet->pos, SHADOWTYPE_BULLET, false);
				}
			}
		}
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//�e�̕`�揈��
//===============================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_3D *pVtx = 0;						//���_���ւ̃|�C���^
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�擾�p
	int nCntBullet;

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].g_mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);

			//�t�s������߂�
			g_aBullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
			g_aBullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
			g_aBullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 
				g_aBullet[nCntBullet].pos.x, 
				g_aBullet[nCntBullet].pos.y, 
				g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].g_mtxWorldBullet, &g_aBullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//===============================================
//�e�̐ݒ菈��
//===============================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	VERTEX_3D *pVtx = 0;   //���_���ւ̃|�C���^
	int nCntBullet;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�

			g_aBullet[nCntBullet].bUse = true;   //�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nLife = nLife;

			//�e��ݒ�
			g_aBullet[nCntBullet].g_nIdxBulletShadow = SetShadow();
			
			break;
		}
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//===============================================
//�Ǐ��̎擾
//===============================================
void GetWall(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, int nCntWall)
{
	posWallS[nCntWall] = pos0;
	posWallE[nCntWall] = pos1;
	vecLine[nCntWall] = posWallE[nCntWall] - posWallS[nCntWall];
}