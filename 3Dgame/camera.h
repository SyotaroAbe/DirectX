//=========================================================
//
//3D�Q�[��[camera.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _CAMERA_H_  //���̃}�N����`������ĂȂ�������
#define _CAMERA_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define ZERO			(0.0f)		//0

//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	float fLength;
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera * GetCamera(void);

#endif