//=========================================================
//
//3Dゲーム[input.h]
//Author = 阿部翔大郎
//
//=========================================================

#ifndef _INPUT_H_   //このマクロ定義がされてなかったら
#define _INPUT_H_   //２重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif