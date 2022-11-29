//=========================================================
//
//3D�Q�[��[shadow.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _SHADOW_H_  //���̃}�N����`������ĂȂ�������
#define _SHADOW_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�e�̎��
typedef enum
{
	SHADOWTYPE_PLAYER = 0,	//�v���C���[
	SHADOWTYPE_BULLET,		//�e
	SHADOWTYPE_MAX
}SHADOWTYPE;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nTdxShadow, D3DXVECTOR3 pos, int type, bool bUse);

#endif