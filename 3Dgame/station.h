//=========================================================
//
//3D�Q�[��[station.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _STATION_H_  //���̃}�N����`������ĂȂ�������
#define _STATION_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

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
	int g_nIdxShadow = -1;
}Station;

//�v���g�^�C�v�錾
void InitStation(void);
void UninitStation(void);
void UpdateStation(void);
void DrawStation(void);
Station * GetStation(void);

#endif