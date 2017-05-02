// yuv.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include "yuv.h"
#include "yuv4.h"

#include "rawvideo420.h"

#include "yuv_setting.h"

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;                                // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��

TCHAR temp_filename[1024];
unsigned char rgb_buf[BUF_MAX];

filebuffer g_filebuffer;




// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HMENU    m_hMenu;
HMENU    m_hSubMenu;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �����ɃR�[�h��}�����Ă��������B

	YuvSetting::GetInst().InitSetting();

    // �O���[�o������������������Ă��܂��B
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_YUV, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // �A�v���P�[�V�����̏����������s���܂�:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YUV));

	m_hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	m_hSubMenu = GetSubMenu(m_hMenu, 0);

    MSG msg;

    // ���C�� ���b�Z�[�W ���[�v:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YUV));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_YUV);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIEGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void setFormat(HWND hWnd, int wmId)
{
	HMENU m = GetMenu(hWnd);

	CheckMenuItem(m, ID_FORMAT_YV12, MF_UNCHECKED);
	CheckMenuItem(m, ID_FORMAT_YUV44, MF_UNCHECKED);

	CheckMenuItem(m, wmId, MF_CHECKED);

	switch (wmId) {
		case ID_FORMAT_YV12:
			YuvSetting::GetInst().SetFormat(YuvSetting::YUV_FORMAT_YV12);
			break;
		case ID_FORMAT_YUV44:
			YuvSetting::GetInst().SetFormat(YuvSetting::YUV_FORMAT_YUV4);
			break;
		default:
			break;
	}

	return;
}

void setViewSize(HWND hWnd, int wmId)
{
	HMENU m = GetMenu(hWnd);

	CheckMenuItem(m, ID_VIEW_1_1, MF_UNCHECKED);
	CheckMenuItem(m, ID_VIEW_1_2, MF_UNCHECKED);
	CheckMenuItem(m, ID_VIEW_1_4, MF_UNCHECKED);

	CheckMenuItem(m, wmId, MF_CHECKED);

	return;

}

int setPixel(HWND hWnd, int wmId)
{
	HMENU m = GetMenu(hWnd);

	CheckMenuItem(m, ID_PIXEL_352X288, MF_UNCHECKED);
	CheckMenuItem(m, ID_PIXEL_1920X1080, MF_UNCHECKED);

	CheckMenuItem(m, wmId, MF_CHECKED);
	switch (wmId) {
	case ID_PIXEL_352X288:
		YuvSetting::GetInst().SetSize(YuvSetting::YUV_SIZE_352_288);
		break;
	case ID_PIXEL_1920X1080:
		YuvSetting::GetInst().SetSize(YuvSetting::YUV_SIZE_1920_1080);
		break;
	default:
		break;
	}

	return 0;
}

int getFrameBufferSize(void)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
		return RawVideo420::getFrameBufferSize(width, height);
	}
	else {
		return Yuv4::getFrameBufferSize(width, height);
	}
	return 0;
}

void getrgb(unsigned char *yuvbuffer)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

	if (YuvSetting::GetInst().GetFormat() == YuvSetting::YUV_FORMAT_YV12) {
			RawVideo420::getRgb(yuvbuffer, width, height, rgb_buf, TRUE, TRUE, TRUE);
	}
	else {
		Yuv4::getRgb(yuvbuffer, width, height, rgb_buf, TRUE, TRUE, TRUE);
	}
	return;
}

int wm_command(HWND hWnd, WPARAM wParam)
{
	int wmId = LOWORD(wParam);
	// �I�����ꂽ���j���[�̉��:
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_PIXEL_352X288:
	case ID_PIXEL_1920X1080:
		setPixel(hWnd, wmId);
		break;
	case ID_VIEW_1_1:
	case ID_VIEW_1_2:
	case ID_VIEW_1_4:
		setViewSize(hWnd, wmId);
		break;
	case ID_FORMAT_YV12:
	case ID_FORMAT_YUV44:
		setFormat(hWnd, wmId);
		break;
	default:
		return -1;
	}
	return 0;

}
void wm_paint(HWND hWnd)
{
	uint32_t width = YuvSetting::GetInst().GetWidthSize();
	uint32_t height = YuvSetting::GetInst().GetHeightSize();

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
	//memset(rgb_buf, 0x00, BUF_MAX);
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
void wm_dropfile(HWND hWnd, WPARAM wParam)
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
	g_filebuffer.create(temp_filename, CACHE_MEMORY_SIZE);

	InvalidateRect(hWnd, NULL, FALSE);
	return;
}
void wm_timer(HWND hWnd)
{
	int yuv_offset = 0;
	int framesize = getFrameBufferSize();
	unsigned char *yuv_buffer = (unsigned char *)malloc(framesize*2);
	if (yuv_buffer == NULL) {
		return;
	}

	unsigned long ret;
	g_filebuffer.read(yuv_buffer, yuv_offset, framesize, &ret);
	if (framesize != ret) {
		//�{���̓G���[����
	}
	getrgb(yuv_buffer);

	free(yuv_buffer);

	InvalidateRect(hWnd, NULL, FALSE);

}
void wm_craete(HWND hWnd)
{
	//�E�B���h�E���h���b�N���h���b�v���󂯕t����悤�ɂ���B
	DragAcceptFiles(hWnd, TRUE);
	SetTimer(hWnd, 1, UPDATE_WINDOW_TIME, NULL);
	return;
}

//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:    ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND  - �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT    - ���C�� �E�B���h�E�̕`��
//  WM_DESTROY  - ���~���b�Z�[�W��\�����Ė߂�
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case WM_CREATE:
		wm_craete(hWnd);
		
		break;

    case WM_COMMAND:
		{
			int ret = wm_command(hWnd, wParam);
			if (ret < 0) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
        break;
    case WM_PAINT:
		wm_paint(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_DROPFILES:
		wm_dropfile(hWnd, wParam);
		break;
	case WM_TIMER:
		wm_timer(hWnd);
		break;
	case WM_RBUTTONUP:
		POINT pos;
		pos.x = LOWORD(lParam);
		pos.y = HIWORD(lParam);

		ClientToScreen(hWnd, &pos);
		TrackPopupMenu(m_hSubMenu, TPM_LEFTALIGN, pos.x, pos.y, 0, hWnd, NULL);
		break;

	default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
