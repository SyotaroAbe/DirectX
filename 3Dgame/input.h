//=========================================================
//
//3D�Q�[��[input.h]
//Author = �����đ�Y
//
//=========================================================

#ifndef _INPUT_H_   //���̃}�N����`������ĂȂ�������
#define _INPUT_H_   //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif