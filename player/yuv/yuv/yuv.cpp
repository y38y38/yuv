// yuv.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <windef.h>
#include <Winuser.h>

#include "resource.h"

#include "yuv_setting.h"
#include "window_manager.h"
#include "image_manager.h"

#include "yuv.h"


#define MAX_LOADSTRING 100


#define RGB_BUF_MAX (4096*2160*3*2) /* 4K(4096x2160) RGB (x3) 16bit (x2) */
#define YUV_BUF_MAX (4096*2160*3*2) /* 4K(4096x2160) RGB (x3) 16bit (x2) */



// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

unsigned char rgb_buf[RGB_BUF_MAX];


// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wcex.lpszMenuName = NULL;
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

   uint32_t width = YuvSetting::GetInst().GetWidthSize();
   uint32_t height = YuvSetting::GetInst().GetHeightSize();
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
	   CW_USEDEFAULT, 0, width, height, nullptr, nullptr, NULL, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


int wm_command(HWND hWnd, WPARAM wParam)
{
	int wmId = LOWORD(wParam);
	// 選択されたメニューの解析:
	switch (wmId)
	{
	case ID_PIXEL_352X289:
	case ID_PIXEL_1920X1081:
		WindowManager::GetInst().SetPixel(m_hSubMenu, hWnd, wmId);
		break;
	case ID_DUMMY_EXIT:
		DestroyWindow(hWnd);
		break;

	default:
		return -1;
	}
	return 0;

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
	static ImageManager img;

    switch (message)
    {
	case WM_CREATE:
		WindowManager::GetInst().Create(hWnd);
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
		{
			uint32_t width = YuvSetting::GetInst().GetWidthSize();
			uint32_t height = YuvSetting::GetInst().GetHeightSize();

			WindowManager::GetInst().Paint(hWnd, width, height, rgb_buf);
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_DROPFILES:
		{	
			TCHAR temp_filename[1024];
			uint32_t width = YuvSetting::GetInst().GetWidthSize();
			uint32_t height = YuvSetting::GetInst().GetHeightSize();

			WindowManager::GetInst().DropFile(hWnd, wParam, temp_filename);
			img.Init(temp_filename);
			img.Update(0, width, height, rgb_buf);

		}
		break;
	case WM_RBUTTONUP:
		WindowManager::GetInst().MouseRight(m_hSubMenu, hWnd, lParam);
		break;
	case WM_LBUTTONDOWN:
		WindowManager::GetInst().MouseLeft(hWnd, lParam);
		break;
	default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

