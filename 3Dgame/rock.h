//=========================================================
//
//3D�Q�[��[rock.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _ROCK_H_  //���̃}�N����`������ĂȂ�������
#define _ROCK_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

//���f���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotDest;	//�ړI�̌���
	float fRotDiff;			//�ړI�̌����܂ł̍���
	bool bMove;				//��������
	int g_nIdxShadow = -1;
}Rock;

//�v���g�^�C�v�錾
void InitRock(void);
void UninitRock(void);
void UpdateRock(void);
void DrawRock(void);
Rock * GetRock(void);

#endif