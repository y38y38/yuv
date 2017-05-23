// yuv.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include <stdio.h>  

#include <windef.h>
#include <Winuser.h>


#include "yuv.h"

#include "yuv_debug.h"
#include "window_manager.h"

#include "resource.h"


#define MAX_LOADSTRING 100



// �O���[�o���ϐ�:
HINSTANCE hInst;                                // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��



// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
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

    // TODO: �����ɃR�[�h��}�����Ă��������B

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
	wcex.lpszMenuName = NULL;
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

   uint32_t width = WindowManager::GetInst().GetWidthSize();
   uint32_t height = WindowManager::GetInst().GetHeightSize();
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
	// �I�����ꂽ���j���[�̉��:
	switch (wmId)
	{
	case ID_PIXEL_352X289:
	case ID_PIXEL_1920X1081:
		WindowManager::GetInst().SetYuvPixel(m_hSubMenu, hWnd, wmId);
		break;
	case ID_VIEW_SINGLE:
	case ID_VIEW_SIDEBYSIDE:
		WindowManager::GetInst().SetYuvView(m_hSubMenu, hWnd, wmId);
		break;
	case ID_DIFF_DISABLE:
	case ID_DIFF_ENABLE:
	case ID_DIFF_ONMOUSE:
		WindowManager::GetInst().SetYuvDiffMode(m_hSubMenu, hWnd, wmId);
		break;
	case ID_DIFFTIMES_X1:
	case ID_DIFFTIMES_X10:
		WindowManager::GetInst().SetYuvDiffTimes(m_hSubMenu, hWnd, wmId);
		break;
	case ID_TEXT_NONE:
	case ID_TEXT_FILENAME:
	case ID_TEXT_SN:
		WindowManager::GetInst().SetYuvText(m_hSubMenu, hWnd, wmId);
		break;
	case ID_POSITION_TOP:
	case ID_POSITION_BOTTOM:
		WindowManager::GetInst().SetYuvTextPosition(m_hSubMenu, hWnd, wmId);
		break;
	case ID_COLOR_BLACK:
	case ID_COLOR_WHITE:
		WindowManager::GetInst().SetYuvTextColor(m_hSubMenu, hWnd, wmId);
		break;
	case ID_SIGNAL_Y:
	case ID_SIGNAL_CB:
	case ID_SIGNAL_CR:
		WindowManager::GetInst().SetYuvSignal(m_hSubMenu, hWnd, wmId);
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
		WindowManager::GetInst().Paint(hWnd);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_DROPFILES:
		WindowManager::GetInst().DropFile(hWnd, wParam);
		break;
	case WM_RBUTTONUP:
		WindowManager::GetInst().MouseRight(m_hSubMenu, hWnd, lParam);
		break;
	case WM_LBUTTONDOWN:
		WindowManager::GetInst().MouseLeft(hWnd, lParam);
		break;
	case WM_KEYDOWN:
		{
			int ret = WindowManager::GetInst().KeyDown(wParam);
			if (ret < 0) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

		}
		break;
	case WM_MOUSEMOVE:
		WindowManager::GetInst().MouseMove();
		break;
	case WM_MOUSELEAVE:
		WindowManager::GetInst().MouseLeave();
		break;
	default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

