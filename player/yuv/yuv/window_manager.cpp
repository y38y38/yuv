#include "stdafx.h"

#include <shellapi.h>

#include "resource.h"

#include "yuv_setting.h"

#include "window_manager.h"


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
	//�E�B���h�E���h���b�N���h���b�v���󂯕t����悤�ɂ���B
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
void WindowManager::DropFile(HWND hWnd, WPARAM wParam, TCHAR *temp_filename)
{
	HDROP  hDrop = NULL;

	//�h���b�N���h���b�v���ꂽ�t�@�C���������o�������B
	hDrop = (HDROP)wParam;
	DWORD   dwDropped;
	dwDropped = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
	//�����A��x��3�t�@�C���ȏ���͂��ꂽ�ꍇ�A�Ō��3�t�@�C������͑ΏۂƂ���B
	for (DWORD i = 0; i < dwDropped; i++) {
		DragQueryFile(hDrop, 0, temp_filename, MAX_PATH);
	}
	DragFinish(hDrop);

	InvalidateRect(hWnd, NULL, FALSE);
	return;
}
void WindowManager::Paint(HWND hWnd, uint32_t width, uint32_t height, unsigned char *rgb_buf)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: HDC ���g�p����`��R�[�h�������ɒǉ����Ă�������...
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
	//�k�����Y��ɂ���֐�
	SetStretchBltMode(hdc, HALFTONE);
	StretchDIBits(hdc,
		0,//x���W 
		0,//y���W
		width,//���� 
		(height),//�c��
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

void WindowManager::SetPixel(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_PIXEL_352X289, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_PIXEL_1920X1081, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_PIXEL_352X289:
		YuvSetting::GetInst().SetSize(YuvSetting::YUV_SIZE_352_288);
		break;
	case ID_PIXEL_1920X1081:
		YuvSetting::GetInst().SetSize(YuvSetting::YUV_SIZE_1920_1080);
		break;
	default:
		break;
	}

	return;

}


