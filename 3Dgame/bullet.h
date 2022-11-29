//=========================================================
//
//3D�Q�[��[bullet.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _BULLET_H_  //���̃}�N����`������ĂȂ�������
#define _BULLET_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define BULLET_LIFE		(50)	//�e�̗̑�

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void GetWall(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, int nCntWall);

#endif