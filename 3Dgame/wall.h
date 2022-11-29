//=========================================================
//
//3D�Q�[��[wall.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _WALL_H_  //���̃}�N����`������ĂȂ�������
#define _WALL_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

//�ǂ̎��
typedef enum
{
	WALLTYPE_NORMAL = 0,	//�ʏ�
	WALLTYPE_INVISIBLE,		//����
	WALLTYPE_MAX
}WALLTYPE;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);

#endif