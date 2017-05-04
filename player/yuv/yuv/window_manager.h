#pragma once
#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "stdint.h"

#include <Winuser.h>

class WindowManager {
public:
	static WindowManager& GetInst(void) {
		static WindowManager singleton;
		return singleton;
	}
	void Create(HWND hWnd);
	void MouseLeft(HWND hWnd, LPARAM lParam);
	void MouseRight(HMENU hSubMenu, HWND hWnd, LPARAM lParam);
	void DropFile(HWND hWnd, WPARAM wParam, TCHAR *temp_filename);
	void Paint(HWND hWnd, uint32_t width, uint32_t height, unsigned char *rgb_buf);
	void SetPixel(HMENU hSubMenu, HWND hWnd, int wmId);

private:
	WindowManager();
	~WindowManager();

};

#endif //_WINDOW_MANAGER_H_


