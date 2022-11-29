//=========================================================
//
//3D�Q�[��[meshwall.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _MESHWALL_H_  //���̃}�N����`������ĂȂ�������
#define _MESHWALL_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

//�}�N����`
#define MAX_MESHWALL	(4)			//�ő�ǐ�
#define WALL_SIZE		(-1980.0f)	//�ǃT�C�Y

//�Ǎ\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	int nMeshwallType;				//�^�C�v
	D3DXMATRIX mtxWorldMeshwall;	//���[���h�}�g���b�N�X
	bool bUse;
}MeshWall;

//�ǂ̎��
typedef enum
{
	MESHWALLTYPE_NORMAL = 0,	//�ʏ�
	MESHWALLTYPE_INVISIBLE,		//����
	MESHWALLTYPE_MAX
}MESHWALLTYPE;

//�v���g�^�C�v�錾
void InitMeshwall(void);
void UninitMeshwall(void);
void UpdateMeshwall(void);
void DrawMeshwall(void);
void SetMeahwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);

#endif