//=========================================================
//
//3D�Q�[��[explosion.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"

//�}�N����`
#define MAX_EXPLOSION   (128)   //�����̍ő吔

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXMATRIX g_mtxWorldBullet;	//���[���h�}�g���b�N�X
	int nCounterAnimExplosion;		//�A�j���[�V�����J�E���^�[
	int nPatternAnimExplosion;		//�A�j���[�V�����p�^�[��No.
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Explosion;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;        //DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;   //���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];                //�����̏��

//===============================================
//�����̏���������
//===============================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_3D *pVtx = 0;						//���_���ւ̃|�C���^
	int nCntExplosion;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//�e�̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(6000.0f, 375.0f, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-16.0f, 16.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-16.0f, -16.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(16.0f, -16.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//===============================================
//�����̏I������
//===============================================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//===============================================
//�����̍X�V����
//===============================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_3D *pVtx = 0;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���

			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;   //�J�E���^�[�����Z

			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % 5) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;   //�J�E���^�[�������l�ɖ߂�
				g_aExplosion[nCntExplosion].nPatternAnimExplosion++;

				//���_�J���[�̍X�V
				pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));
				pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f - (g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.1f));

				//�e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion *0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnimExplosion  > 7)
				{//���p�^�[�����𒴂���
					g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;

					g_aExplosion[nCntExplosion].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���
				}
			}
		}
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//===============================================
//�����̕`�揈��
//===============================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_3D *pVtx = 0;						//���_���ւ̃|�C���^
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�擾�p
	int nCntExplosion;

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].g_mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aExplosion[nCntExplosion].g_mtxWorldBullet, NULL, &mtxView);

			//�t�s������߂�
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._41 = 0.0f;
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._42 = 0.0f;
			g_aExplosion[nCntExplosion].g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aExplosion[nCntExplosion].pos.x,
				g_aExplosion[nCntExplosion].pos.y,
				g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].g_mtxWorldBullet,
				&g_aExplosion[nCntExplosion].g_mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
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
//�����̐ݒ菈��
//===============================================
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCntExplosion;
	VERTEX_3D *pVtx = 0;   //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].bUse = true;   //�g�p���Ă����Ԃɂ���
			g_aExplosion[nCntExplosion].pos = pos;

			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;   //�J�E���^�[�����Z�b�g


			break;
		}
		pVtx += 4;   //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}