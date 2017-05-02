// yuv.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "yuv.h"
#include "yuv4.h"

#include "rawvideo420.h"

#include "yuv_setting.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

TCHAR temp_filename[1024];
unsigned char rgb_buf[BUF_MAX];

filebuffer g_filebuffer;




// このコード モジュールに含まれる関数の宣言を転送します:
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

    // TODO: ここにコードを挿入してください。

	YuvSetting::GetInst().InitSetting();

    // グローバル文字列を初期化しています。
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_YUV, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーションの初期化を実行します:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YUV));

	m_hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	m_hSubMenu = GetSubMenu(m_hMenu, 0);

    MSG msg;

    // メイン メッセージ ループ:
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
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
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

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
	// 選択されたメニューの解析:
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
	//memset(rgb_buf, 0x00, BUF_MAX);
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
void wm_dropfile(HWND hWnd, WPARAM wParam)
{
	HDROP  hDrop = NULL;
	//ドラック＆ドロップされたファイル名を取り出す処理。
	hDrop = (HDROP)wParam;
	DWORD   dwDropped;
	dwDropped = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
	//もし、一度に3ファイル以上入力された場合、最後の3ファイルを解析対象とする。
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
		//本当はエラー処理
	}
	getrgb(yuv_buffer);

	free(yuv_buffer);

	InvalidateRect(hWnd, NULL, FALSE);

}
void wm_craete(HWND hWnd)
{
	//ウィンドウがドラック＆ドロップを受け付けるようにする。
	DragAcceptFiles(hWnd, TRUE);
	SetTimer(hWnd, 1, UPDATE_WINDOW_TIME, NULL);
	return;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウの描画
//  WM_DESTROY  - 中止メッセージを表示して戻る
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

// バージョン情報ボックスのメッセージ ハンドラーです。
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
