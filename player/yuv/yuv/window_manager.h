#pragma once
#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "stdint.h"
#include <Winuser.h>

#include "yuv_player.h"

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
	void DropFile(HWND hWnd, WPARAM wParam);
	void Paint(HWND hWnd);
	void SetYuvPixel(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvView(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvDiffMode(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvDiffTimes(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvText(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvTextPosition(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvTextColor(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetYuvSignal(HMENU hSubMenu, HWND hWnd, int wmId);
	int KeyDown(WPARAM wParam);
	void MouseMove(void);
	void MouseLeave(void);

	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
	void Update(void);


private:
	WindowManager();
	~WindowManager();

	void UpdateWindowSize(void);
	YuvPlayer Player;
	HWND MyWindow;
	YuvPlayer::YUV_WINDOW_POS GetMousePosition(void);

	int Text;
	int TextPosition;
	int TextColor;

	void ShowText(HDC hdc);

	int GetTextPosition(int file_num, int index);
	void ShowTextFileName(HDC hdc);

	void ShowRgb(HDC hdc);

	bool ToggleAndGetStatus(HMENU submenu, int id);

	

};

#endif //_WINDOW_MANAGER_H_


