//=========================================================
//
//3D�Q�[��[model.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _MODEL_H_  //���̃}�N����`������ĂȂ�������
#define _MODEL_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

//�}�N����`
#define MAX_TEXTURE			(24)		//�ő�e�N�X�`����
#define ROT_DIFF_PI			(2.0f)		//�p�x�̒l�̕␳
#define ROT_CAMERA			(1.0f)		//�J�����̌����ɍ��킹�ē�����
#define ROT_CAMERA_DIFF		(0.1f)		//�p�x�̕␳�W���i�����傫�����f�����ς��j
#define MIN_VTX				(900.0f)	//vtx�ŏ��l�����l
#define MAX_VTX				(-900.0f)	//vtx�ő�l�����l

//���f���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 vecmove;	//�ړ��x�N�g��
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotDest;	//�ړI�̌���
	float fRotDiff;			//�ړI�̌����܂ł̍���
	bool bMove;				//��������
}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model * GetModel(void);

#endif