#include "stdafx.h"

#include "stdlib.h"
#include <shellapi.h>

#include "resource.h"

#include "yuv_debug.h"
#include "yuv_setting.h"
#include "yuv_player.h"
#include "yuv_str.h"

#include "window_manager.h"

#define	MAX_YUV_FILENAME	(1024)



WindowManager::WindowManager()
{
	Text = ID_TEXT_NONE;
	TextPosition = ID_POSITION_TOP;
	TextColor = ID_COLOR_BLACK;
	Key = 0x0;
	Continus = 0x0;
	return;
}
WindowManager::~WindowManager()
{
	return;
}

void WindowManager::Create(HWND hWnd)
{
	MyWindow = hWnd;
	Player.Init();
	//ウィンドウがドラック＆ドロップを受け付けるようにする。
	DragAcceptFiles(hWnd, TRUE);

	
	return;
}

void WindowManager::SetMenuSetPixel(HMENU submenu)
{
	uint32_t width = Player.GetWidthSize();
	if (width == 352) {
		CheckMenuItem(submenu, ID_PIXEL_352X289, MF_CHECKED);

	}
	else {
		CheckMenuItem(submenu, ID_PIXEL_1920X1081, MF_CHECKED);
	}
	return;
}
void WindowManager::SetMenuSetFormat(HMENU submenu)
{
	YuvSetting::YuvFormat format = Player.GetFormat();
	if (format == YuvSetting::YUV_FORMAT_YUV4) {
		CheckMenuItem(submenu, ID_FORMAT_YUV4, MF_CHECKED);

	}
	else {
		CheckMenuItem(submenu, ID_FORMAT_CMM, MF_CHECKED);
	}
	return;
}

void WindowManager::SetMenuSetView(HMENU submenu)
{
	YuvSetting::YuvView view = Player.GetView();
	if (view == YuvSetting::YUV_VIEW_SINGLE) {
		CheckMenuItem(submenu, ID_VIEW_SINGLE, MF_CHECKED);
	}
	else {
		CheckMenuItem(submenu, ID_VIEW_SIDEBYSIDE, MF_CHECKED);
	}
	return;

}
void WindowManager::SetMenuSetDiffMode(HMENU submenu)
{
	YuvSetting::YuvDiffMode mode = Player.GetDiffMode();
	if (mode == YuvSetting::YUV_DIFF_DISABLE) {
		CheckMenuItem(submenu, ID_DIFF_DISABLE, MF_CHECKED);
	}
	else if (mode == YuvSetting::YUV_DIFF_ENABLE) {
		CheckMenuItem(submenu, ID_DIFF_ENABLE, MF_CHECKED);

	}
	else {
		CheckMenuItem(submenu, ID_DIFF_ONMOUSE, MF_CHECKED);
	}
	return;

}
void WindowManager::SetMenuSetDiffTimes(HMENU submenu)
{
	int difftimes = Player.GetDiffTimes();

	if (difftimes == 1) {
		CheckMenuItem(submenu, ID_DIFFTIMES_X1, MF_CHECKED);

	}
	else {
		CheckMenuItem(submenu, ID_DIFFTIMES_X10, MF_CHECKED);
	}
	return;

}
void WindowManager::SetMenuSetSignal(HMENU submenu)
{
	bool y = Player.GetSignalY();
	if (y == true) {
		CheckMenuItem(submenu, ID_SIGNAL_Y, MF_CHECKED);

	}

	bool cb = Player.GetSignalCb();
	if (cb == true) {
		CheckMenuItem(submenu, ID_SIGNAL_CB, MF_CHECKED);
	}

	bool cr = Player.GetSignalCr();
	if (cr == true) {
		CheckMenuItem(submenu, ID_SIGNAL_CR, MF_CHECKED);
	}
	return;

}

void WindowManager::MenuInit(HMENU hSubMenu)
{
	//Windowの初期値を設定する
	SetMenuSetPixel(hSubMenu);
	SetMenuSetFormat(hSubMenu);
	SetMenuSetView(hSubMenu);
	SetMenuSetDiffMode(hSubMenu);
	SetMenuSetDiffTimes(hSubMenu);
	SetMenuSetSignal(hSubMenu);
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

int WindowManager::GetTextPositionHeight(int file_num, int index)
{
	if (file_num < 3) {
		if (TextPosition == ID_POSITION_TOP) {
			return  0;
		}
		else {
			return Player.GetHeightSize() - 20;
		}

	}
	else
	{
		if (index < 2) {
			if (TextPosition == ID_POSITION_TOP) {
				return  0;
			}
			else {
				return (Player.GetHeightSize() / 2) - 20;
			}
		}
		else {
			if (TextPosition == ID_POSITION_TOP) {
				return (Player.GetHeightSize() / 2);
			}
			else {
				return Player.GetHeightSize() - 20;
			}

		}

	} 
}
int WindowManager::GetTextPositionWidth(int file_num, int index)
{
	if ((index % 2) == 0) {
		return 0;
	}
	else {
		return (Player.GetWidthSize() / 2);
	}
}

void WindowManager::ShowTextFileName(HDC hdc)
{
	YuvSetting::YuvView view =  Player.GetView();
	if (view == YuvSetting::YUV_VIEW_SIDE_BY_SIDE) {
		int file_num = Player.GetFileNum();
		SetBkMode(hdc, TRANSPARENT);

		for (int index = 0; index < file_num; index++) {
			TCHAR *path = Player.GetFileName(index);
			TCHAR *filename = YuvStr::GetFileName(path);
			TextOut(hdc, GetTextPositionWidth(file_num, index), GetTextPositionHeight(file_num, index), filename, _tcslen(filename));
		}
	}
	else {
		int index = Player.GetViewIndex();
		SetBkMode(hdc, TRANSPARENT);
		TCHAR *path = Player.GetFileName(index);
		TCHAR *filename = YuvStr::GetFileName(path);

		TextOut(hdc, 0, GetTextPositionHeight(1,0), filename, _tcslen(filename));


	}

}
void WindowManager::ShowText(HDC hdc)
{

	if (TextColor == ID_COLOR_BLACK) {
		SetTextColor(hdc, RGB(0x00, 0x00, 0x00));
	}
	else {
		SetTextColor(hdc, RGB(0xff, 0xff, 0xff));

	}
	if (Text == ID_TEXT_FILENAME) {
		ShowTextFileName(hdc);
	}
	else if (Text == ID_TEXT_SN) {
		 
	}
	else {

	}

}
void WindowManager::ShowRgb(HDC hdc)
{
	uint32_t width = Player.GetWidthSize();
	uint32_t height = Player.GetHeightSize();
	uint8_t *rgb_buf = Player.GetRgbBuf();

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

}

void WindowManager::Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	ShowRgb(hdc);
	ShowText(hdc);

	EndPaint(hWnd, &ps);
	return;

}
void WindowManager::UpdateWindowSize(void)
{
	//Windowサイズを変更する。
	RECT rc1;
	int width = Player.GetWidthSize();
	int height = Player.GetHeightSize();
	GetWindowRect(MyWindow, &rc1);
	SetWindowPos(MyWindow, NULL, rc1.left, rc1.top, width, height, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

}

void WindowManager::SetYuvPixel(HMENU hSubMenu, HWND hWnd, int wmId)
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
	return;

}
void WindowManager::SetYuvFormat(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_FORMAT_YUV4, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_FORMAT_CMM, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_FORMAT_YUV4:
		Player.SetFormat(YuvSetting::YUV_FORMAT_YUV4);
		break;
	case ID_FORMAT_CMM:
		Player.SetFormat(YuvSetting::YUV_FORMAT_CMM);
		break;
	default:
		break;
	}
	return;

}
void WindowManager::SetYuvView(HMENU hSubMenu, HWND hWnd, int wmId)
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
	return;

}
void WindowManager::SetYuvDiffMode(HMENU hSubMenu, HWND hWnd, int wmId)
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
void WindowManager::SetYuvDiffTimes(HMENU hSubMenu, HWND hWnd, int wmId)
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
void WindowManager::SetYuvText(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_TEXT_NONE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_TEXT_FILENAME, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_TEXT_SN, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_TEXT_NONE:
		break;
	case ID_TEXT_FILENAME:
		break;
	case ID_TEXT_SN:
		break;
	default:
		break;
	}
	Text = wmId;
	return;
}

void WindowManager::SetYuvTextPosition(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_POSITION_TOP, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_POSITION_BOTTOM, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_POSITION_TOP:
		break;
	case ID_POSITION_BOTTOM:
		break;
	default:
		break;
	}
	TextPosition = wmId;
	return;
}
void WindowManager::SetYuvTextColor(HMENU hSubMenu, HWND hWnd, int wmId)
{
	CheckMenuItem(hSubMenu, ID_COLOR_BLACK, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, ID_COLOR_WHITE, MF_UNCHECKED);

	CheckMenuItem(hSubMenu, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_COLOR_BLACK:
		break;
	case ID_COLOR_WHITE:
		break;
	default:
		break;
	}

	TextColor = wmId;

	return;
}
bool WindowManager::ToggleAndGetStatus(HMENU submenu, int id)
{
	UINT  status = GetMenuState(submenu, id, MF_BYCOMMAND);

	if (status == MF_CHECKED) {
		CheckMenuItem(submenu, id, MF_UNCHECKED);
		return false;
	}
	else {
		CheckMenuItem(submenu, id, MF_CHECKED);
		return true;
	}
}


void WindowManager::SetYuvSignal(HMENU hSubMenu, HWND hWnd, int wmId)
{
	bool status = ToggleAndGetStatus(hSubMenu, wmId);
	switch (wmId) {
	case ID_SIGNAL_Y:
		Player.SetSignalY(status);
		break;
	case ID_SIGNAL_CB:
		Player.SetSignalCb(status);
		break;
	case ID_SIGNAL_CR:
		Player.SetSignalCr(status);
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
	Win32Printf("%hs %d %x", __FUNCTION__, __LINE__, wParam);
	int continous = GetKeyContinous();
	switch (wParam)
	{
	case 0x20://space
		Player.NextFrame();
		break;
	case 0x25://←
		if (continous != 0) {
			Player.JumpFrame(-1 * continous);
		}
		else {
			Player.PrevFrame();
		}
		break;
	case 0x26://↑
		Player.NextImage();
		break;
	case 0x27://→
		if (continous != 0) {
			Player.JumpFrame(continous);
		} else {
			Player.NextFrame();
		}
		break;
	case 0x28://↓
		Player.PrevImage();
		break;
	default:
		return -1;
		break;
	}
	SetKeyLog(TRUE, wParam);
	return 0;
}
int WindowManager::KeyUp(WPARAM wParam)
{
	Win32Printf("%hs %d %x", __FUNCTION__, __LINE__,wParam);
	switch (wParam)
	{
	case 0x25://←
	case 0x27://→
		break;
	default:
		return -1;
		break;
	}
	SetKeyLog(FALSE, wParam);
	return 0;
}
void WindowManager::SetKeyLog(BOOL down, WPARAM wParam)
{
	if (down == TRUE) {
		if (Key == wParam) {
			Continus++;
		}
		else {
			Continus = 0;
		}
		Key = wParam;
	}
	else {
		Key = 0;
		Continus = 0;
	}
	return;
}
int WindowManager::GetKeyContinous(void)
{
	return Continus;
}

void WindowManager::Update(void)
{
	UpdateWindowSize();
	InvalidateRect(MyWindow, NULL, FALSE);
	return;
}
YuvPlayer::YUV_WINDOW_POS  WindowManager::GetMousePosition(void)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(MyWindow, &p);
	int width = (int)Player.GetWidthSize();
	int height = (int)Player.GetHeightSize();
	if ((p.x > (width / 2))) {
		if ((p.y) > (height / 2)) {
			return YuvPlayer::YUV_WINDOW_RIGHT_BOTTOM;
		}
		else {
			return YuvPlayer::YUV_WINDOW_RIGHT_TOP;
		}
	}
	else {
		if ((p.y) > (height / 2)) {
			return YuvPlayer::YUV_WINDOW_LEFT_BOTTOM;
		}
		else {
			return YuvPlayer::YUV_WINDOW_LEFT_TOP;
		}
	}

}


void WindowManager::MouseMove(void)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = MyWindow;
	tme.dwHoverTime = HOVER_DEFAULT;

	TrackMouseEvent(&tme);

	Player.SetMouse(GetMousePosition());

	return;
}

void WindowManager::MouseLeave(void)
{
	Player.ReleaseMouse();
	return;
}
