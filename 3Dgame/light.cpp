//=========================================================
//
//3D�Q�[��[light.cpp]
//Author = �����đ�Y
//
//=========================================================

#include"main.h"
#include"light.h"

//�}�N����`
#define MAX_LGHT	(3)	//���C�g�̐�

//�O���[�o���ϐ�
D3DLIGHT9 g_light[MAX_LGHT];	//���C�g�̏��

//===============================================
//���C�g�̏���������
//===============================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;							//�ݒ�p�����x�N�g��
	int nCntLight;

	for (nCntLight = 0; nCntLight < MAX_LGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	}
		//���C�g�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K������
		g_light[0].Direction = vecDir;
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K������
		g_light[1].Direction = vecDir;
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K������
		g_light[2].Direction = vecDir;

	for (nCntLight = 0; nCntLight < MAX_LGHT; nCntLight++)
	{
		//���C�g��ݒ肷��
		pDevice->SetLight(0, &g_light[nCntLight]);
	}

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//===============================================
//���C�g�̏I������
//===============================================
void UninitLight(void)
{
	
}

//===============================================
//���C�g�̍X�V����
//===============================================
void UpdateLight(void)
{

}