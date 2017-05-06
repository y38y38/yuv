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
	void MouseLeft(HWND hWnd, LPARAM lParam);
	void MouseRight(HMENU hSubMenu, HWND hWnd, LPARAM lParam);
	void DropFile(HWND hWnd, WPARAM wParam);
	void Paint(HWND hWnd);
	void SetPixel(HMENU hSubMenu, HWND hWnd, int wmId);
	void SetView(HMENU hSubMenu, HWND hWnd, int wmId);
	int KeyDown(WPARAM wParam);
	uint32_t GetWidthSize(void);
	uint32_t GetHeightSize(void);
	void Update(void);


private:
	WindowManager();
	~WindowManager();
	YuvPlayer Player;
	HWND MyWindow;

};

#endif //_WINDOW_MANAGER_H_


