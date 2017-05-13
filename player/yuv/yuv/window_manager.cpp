#include "stdafx.h"

#include "stdlib.h"
#include <shellapi.h>

#include "resource.h"

#include "yuv_setting.h"
#include "yuv_player.h"

#include "window_manager.h"

#define	MAX_YUV_FILENAME	(1024)



WindowManager::WindowManager()
{
	return;
}
WindowManager::~WindowManager()
{
	return;
}

void WindowManager::Create(HWND hWnd)
{
	Player.Init();
	MyWindow = hWnd;
	//ウィンドウがドラック＆ドロップを受け付けるようにする。
	DragAcceptFiles(hWnd, TRUE);
	return;
}
void WindowManager::MouseLeft(HWND hWnd, LPARAM lParam)
{
	PostMessage(hWnd, WM_NCLBUTTONDOWN, (WPARAM)HTCAPTION, lParam);
	return;
}

void WindowManager::MouseRight(HMENU hSubMenu, HWND hWnd, LPARAM lParam)
{
	POINT pos;
	pos.x = LOWORD(lParam);
	pos.y = HIWORD(lParam);

	ClientToScreen(hWnd, &pos);
	TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, pos.x, pos.y, 0, hWnd, NULL);

	return;
}
void WindowManager::DropFile(HWND hWnd, WPARAM wParam)
{
	TCHAR *filename = (TCHAR*)malloc(sizeof(TCHAR) * MAX_YUV_FILENAME);
	if (filename == NULL) {
		//エラー処理
	}

	HDROP  hDrop = NULL;

	//ドラック＆ドロップされたファイル名を取り出す処理。
	hDrop = (HDROP)wParam;
	DWORD   dwDropped;
	dwDropped = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
	for (DWORD i = 0; i < dwDropped; i++) {
		DragQueryFile(hDrop, 0, filename, MAX_PATH);
		Player.InputFile(filename);
	}
	DragFinish(hDrop);

	free(filename);

	return;
}
void WindowManager::Paint(HWND hWnd)
{

	uint32_t width = Player.GetWidthSize();
	uint32_t height = Player.GetHeightSize();
	uint8_t *rgb_buf = Player.GetRgbBuf();


	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);



	// TODO: HDC を使用する描画コードをここに追加してください...
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biBitCount = 24;
	bitmapinfo.bmiHeader.biClrImportant = 0;
	bitmapinfo.bmiHeader.biClrUsed = 0;
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biSizeImage = 0;
	bitmapinfo.bmiHeader.biWidth = width;
	bitmapinfo.bmiHeader.biHeight = -((LONG)height);
	bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
	bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
	//縮小を綺麗にする関数
	SetStretchBltMode(hdc, HALFTONE);
	StretchDIBits(hdc,
		0,//x座標 
		0,//y座標
		width,//横幅 
		(height),//縦幅
		0,
		0,
		width,
		(height),
		rgb_buf,
		&bitmapinfo,
		DIB_RGB_COLORS,
		SRCCOPY);

	EndPaint(hWnd, &ps);
	return;

}
void WindowManager::UpdateWindowSize(HWND hWnd)
{
	//Windowサイズを変更する。
	RECT rc1;
	int width = Player.GetWidthSize();
	int height = Player.GetHeightSize();
	GetWindowRect(hWnd, &rc1);
	SetWindowPos(hWnd, NULL, rc1.left, rc1.top, width, height, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

}

void WindowManager::SetPixel(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_PIXEL_352X289, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_PIXEL_1920X1081, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_PIXEL_352X289:
		Player.SetPixel(YuvSetting::YUV_SIZE_352_288);
		break;
	case ID_PIXEL_1920X1081:
		Player.SetPixel(YuvSetting::YUV_SIZE_1920_1080);
		break;
	default:
		break;
	}
	UpdateWindowSize(hWnd);
	return;

}
void WindowManager::SetView(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_VIEW_SINGLE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_VIEW_SIDEBYSIDE, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_VIEW_SINGLE:
		Player.SetView(YuvSetting::YUV_VIEW_SINGLE);
		break;
	case ID_VIEW_SIDEBYSIDE:
		Player.SetView(YuvSetting::YUV_VIEW_SIDE_BY_SIDE);
		break;
	default:
		break;
	}
	UpdateWindowSize(hWnd);
	return;

}
void WindowManager::SetDiffMode(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_DIFF_DISABLE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_DIFF_ENABLE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_DIFF_ONMOUSE, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);

	switch (wmId) {
	case ID_DIFF_DISABLE:
		Player.SetDiffMode(YuvSetting::YUV_DIFF_DISABLE);
		break;
	case ID_DIFF_ENABLE:
		Player.SetDiffMode(YuvSetting::YUV_DIFF_ENABLE);
		break;
	case ID_DIFF_ONMOUSE:
		Player.SetDiffMode(YuvSetting::YUV_DIFF_ONMOUSE);
		break;
	default:
		break;
	}
	return;

}
void WindowManager::SetDiffTimes(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_DIFFTIMES_X1, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_DIFFTIMES_X10, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);

	switch (wmId) {
	case ID_DIFFTIMES_X1:
		Player.SetDiffTimes(YuvSetting::YUV_DIFFTIMES_X1);
		break;
	case ID_DIFFTIMES_X10:
		Player.SetDiffTimes(YuvSetting::YUV_DIFFTIMES_X10);
		break;
	default:
		break;
	}
	return;
}


uint32_t WindowManager::GetWidthSize(void)
{
	return Player.GetWidthSize();
}
uint32_t WindowManager::GetHeightSize(void)
{
	return Player.GetHeightSize();

}
int WindowManager::KeyDown(WPARAM wParam)
{
	switch (wParam)
	{
	case 0x25://←
		Player.PrevFrame();
		break;
	case 0x26://↑
		Player.NextImage();
		break;
	case 0x27://→
		Player.NextFrame();
		break;
	case 0x28://↓
		Player.PrevImage();
		break;
	default:
		return -1;
		break;
	}
	return 0;
}
void WindowManager::Update(void)
{
	InvalidateRect(MyWindow, NULL, FALSE);
	return;
}

void WindowManager::MouseMove(void)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = MyWindow;
	tme.dwHoverTime = HOVER_DEFAULT;

	TrackMouseEvent(&tme);

	Player.SetMouse();
	return;
}

void WindowManager::MouseLeave(void)
{
	Player.ReleaseMouse();
	return;
}
