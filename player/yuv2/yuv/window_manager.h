#pragma once
#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "stdint.h"
#include <Winuser.h>

//#include "yuv_player.h"
#include "yuv_reciever.h"

class WindowManager {
public:
	static WindowManager& GetInst(void) {
		static WindowManager singleton;
		return singleton;
	}
	void Create(HWND hWnd);
	void MenuInit(HMENU hSubMenu);
	void MouseLeft(HWND hWnd, LPARAM lParam);
	void MouseRight(HMENU hSubMenu, HWND hWnd, LPARAM lParam);
//	void DropFile(HWND hWnd, WPARAM wParam);
	void Paint(HWND hWnd);
	void SetYuvPixel(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvFormat(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvView(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvDiffMode(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvDiffTimes(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvText(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvTextPosition(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvTextColor(HMENU hSubMenu, HWND hWnd, int wmId);
	//void SetYuvSignal(HMENU hSubMenu, HWND hWnd, int wmId);
	//int KeyDown(WPARAM wParam);
	//int KeyUp(WPARAM wParam);
	void MouseMove(void);
	void MouseLeave(void);

	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
	void Update(void);


private:
	WindowManager();
	~WindowManager();

	//YuvPlayer Player;
	YuvReciever Player;
	HWND MyWindow;
	int Text;
	int TextPosition;
	int TextColor;
	WPARAM Key;
	int Continus;


	void UpdateWindowSize(void);
//	YuvPlayer::YUV_WINDOW_POS GetMousePosition(void);
	
	void ShowText(HDC hdc);

	int GetTextPositionHeight(int file_num, int index);
	int GetTextPositionWidth(int file_num, int index);
	void ShowTextFileName(HDC hdc);

	void ShowRgb(HDC hdc);

	bool ToggleAndGetStatus(HMENU submenu, int id);

	void SetMenuSetPixel(HMENU submenu);
	void SetMenuSetFormat(HMENU submenu);
	void SetMenuSetView(HMENU submenu);
	void SetMenuSetDiffMode(HMENU submenu);
	void SetMenuSetDiffTimes(HMENU submenu);
	void SetMenuSetSignal(HMENU submenu);
	
	void SetKeyLog(BOOL down, WPARAM wParam);
	int GetKeyContinous(void);

};

#endif //_WINDOW_MANAGER_H_


