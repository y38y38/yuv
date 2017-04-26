// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください

#include <windef.h>
#include <Winuser.h>
#include <shellapi.h>

#include "filebuffer.h"

#define BUF_MAX (4096*2160*3*2) /* 4K(4096x2160) RGB (x3) 16bit (x2) */
#define DEFAULT_WIDTH  (352)
#define DEFAULT_HIEGHT (288)

#define DEFAULT_WINDOW_WIDTH  (DEFAULT_WIDTH + 50)
#define DEFAULT_WINDOW_HIEGHT (DEFAULT_HIEGHT + 100)


#define DEFAULT_420_SIZE ((DEFAULT_WIDTH * DEFAULT_HIEGHT) + ((DEFAULT_WIDTH * DEFAULT_HIEGHT) / 2))

#define FORMAT_YV12	(0)
#define FORMAT_YUV4	(1)


#define UPDATE_WINDOW_TIME (2000)

#define	CACHE_MEMORY_SIZE (0)



