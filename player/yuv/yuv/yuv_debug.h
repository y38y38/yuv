#ifndef _YUV_DEBUG_H_
#define _YUV_DEBUG_H_

#
#define		Win32Printf(str, ...) \
      { \
        TCHAR c[256]; \
		SYSTEMTIME local_time; \
		GetLocalTime(&local_time); \
		_stprintf_s( c, _T("%d.%d.%d.%d:"),local_time.wHour, local_time.wMinute, local_time.wSecond, local_time.wMilliseconds); \
        OutputDebugString( c ); \
        _stprintf_s( c, _T(str), __VA_ARGS__ ); \
        OutputDebugString( c ); \
        OutputDebugString( _T("\n") ); \
      }

#endif // _YUV_DEBUG_H_

