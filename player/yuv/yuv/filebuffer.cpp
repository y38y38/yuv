#include "stdafx.h"

#include "windows.h"

#include <string>


#include "filebuffer.h"


filebuffer::filebuffer()
{
	return;
}

filebuffer::~filebuffer()
{
	return;
}

int filebuffer::direct_read(unsigned char *write_buffer, unsigned long long  offset, unsigned long size, unsigned long *result_read_size)
{
	//ファイルオープン
	HANDLE filehandle = CreateFile(input_filename, 
						SYNCHRONIZE|GENERIC_READ ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL,
						NULL
						);
	if (filehandle == INVALID_HANDLE_VALUE) {
		return -1;
	}

	//ファイルシーク
	DWORD now_position;
	LONG setoffset;
	LONG setoffsethigh;
	DWORD dwError;
		
	//オフセットは32bitに分離
	setoffset = (DWORD)(offset&0xffffffff);
	setoffsethigh = (DWORD)((offset&0xffffffff00000000)>>32);

	now_position = SetFilePointer(filehandle, setoffset, &setoffsethigh, FILE_BEGIN);
	if (now_position == INVALID_SET_FILE_POINTER) {
		dwError = GetLastError();
		if (dwError == ERROR_HANDLE_EOF) {
			/// end of file
			CloseHandle(filehandle);
			*result_read_size = 0;
			return 0;
		} else if (dwError != NO_ERROR) {
			//error
			CloseHandle(filehandle);
			return -2;
		} else {
			//OK
		}
	} else {
		//OK
	}
	//ファイルシークここまで


	//ファイルリード
	DWORD readsize;
	BOOL bool_result = ReadFile(filehandle, (LPVOID)write_buffer, size, &readsize, NULL);
	if (bool_result == 0) {
		//error
		CloseHandle(filehandle);
		return -1;
	} else if (readsize == 0) {
		//end of file
		*result_read_size = 0;
		CloseHandle(filehandle);
		return 0;
	} else {
		//読み取り成功
		*result_read_size = readsize;
	}
	CloseHandle(filehandle);

	return 1;
}

#if CACHE_THREAD_ON
#if 1
void filebuffer::thread_run(void)
{
	//スレッド内で行う処理を入れる。
	unsigned long readsize;
	int result = direct_read(cache_memory, internal_file_offset, cache_size, &readsize);
	if (result < 0) {
		return;
	}
	win32DebugString(_T("thead end"));
	ExitThread(0x0);
	return;
}

#else
struct thread_parameter {
	unsigned char *memory;
	unsigned long long offset;
	unsigned long size;
};

struct thread_parameter g_parameter;

DWORD WINAPI filebuffer::ThreadFunc(LPVOID vdParam)
{
	unsigned long readsize;

	//以下をスレッドに移動する。
	direct_read(g_parameter.memory, g_parameter.offset, g_parameter.size, &readsize);

	ExitThread(0x0);
	return 0;
}

#endif
#endif

int filebuffer::cache_update(unsigned long long offset, unsigned long size, unsigned long *result_read_size)
{
#if CACHE_THREAD_ON
	unsigned long readsize;

	//まずはすぐに必要な分だけ読み出して、あとは別スレッドで読み込む。すげー。
	int result = direct_read(cache_memory, offset, size, &readsize);
	if (result < 0) {
		return -1;
	}
	//internal_file_sizeはごまかし。。。
	internal_file_size = cache_size;
	internal_file_offset = offset;

	//以下をスレッドに移動する。
	if (( cache_size - size ) > 0) {
		DWORD dwID;
		CreateThread(NULL , 0 , (LPTHREAD_START_ROUTINE)buffer::EntryPoint , (LPVOID)this , 0 , &dwID);
	}
	return internal_file_size;
#else
	unsigned long readsize;

	//まずはすぐに必要な分だけ読み出して、あとは別スレッドで読み込む。すげー。
	int result = direct_read(cache_memory, offset, cache_size, &readsize);
	if (result < 0) {
		return -1;
	}
	internal_file_size = readsize;
	internal_file_offset = offset;
	return internal_file_size;

#endif
}


//キャッシュサイズが0の場合を考えて。
int filebuffer::create(TCHAR *filename, unsigned long memory_size)
{
	//変数の初期化
	cache_memory = NULL;
	cache_size = 0;
	internal_file_offset = 0;
	internal_file_size = 0;

	//ファイル名の保存
	_tcsncpy_s(input_filename, filename, 1024);

	if (memory_size == 0) {
		//その場合はdirectで毎回読む
		return 0;
	}

	//キャッシュメモリの取得
	cache_memory = (unsigned char *)malloc(memory_size);
	if (cache_memory == NULL) {
		return -1;
	}
	//キャッシュサイズを保存。
	cache_size = memory_size;

//#if CACHE_THREAD_ON
#if 0
	DWORD dwID;
	CreateThread(NULL , 0 , (LPTHREAD_START_ROUTINE)buffer::EntryPoint , (LPVOID)this , 0 , &dwID);

#else
	//createした時は、ファイルの先頭をキャッシュする。
	unsigned long dummy;
	int return_value = cache_update(0, cache_size, &dummy);
	if (return_value < 0) {
		return -1;
	}
#endif

	return 0;
}

int filebuffer::read(unsigned char *buffer, unsigned long long offset, unsigned long size, unsigned long *result_read_size)
{
	int result;

	//リードするサイズが、キャッシュサイズより大きいか確認
	if (size > cache_size) {
		//リードするサイズがキャッシュより大きい場合は、ファイルから
		//直接リードして、バッファにライトする。
		result = direct_read(buffer, offset, size, result_read_size);
		if (result < 0) {
			return -1;
		}
	} else {
		//キャッシュにHITするか確認
		if (offset >= internal_file_offset) {
			//オフセットはキャッシュ内にある。
			
			if ((offset + size) <= (internal_file_offset + internal_file_size)) {
				//リードしたい最後のデータもキャッシュ内にある。
				//HIT
				*result_read_size = size;
			} else {
				//リードしたい最後のデータがキャッシュの外なので、キャシュをやり直し。
				result = cache_update(offset, size, result_read_size);
				if (result < 0) {
					return -1;
				} else if (result == 0) {
					//end of file
					*result_read_size = 0;
					return 0;
				} else {
					//キャッシュにデータ移動完了。
					//実際にコピーするサイズを更新。
					*result_read_size = size;
				}
			}
		} else {
			//リードしたい先頭のデータがキャッシュの外なので、キャシュをやり直し。
			result = cache_update(offset, size, result_read_size);
			if (result < 0) {
				return -1;
			} else if (result == 0) {
				//end of file
				return 0;
			} else {
				//キャッシュにデータ移動完了。
				//実際にコピーするサイズを更新。
				*result_read_size = size;
			}
		}

		//リードしたいデータはキャシュ内にある。
		//sizeでなくreadsizeを使用するのは、例えば、指定されたサイズ分ファイル内にデータがなかった場合等

		memcpy((void*)buffer, cache_memory + (offset - internal_file_offset), *result_read_size);
		result = 0;
	}
	
	return result;
}

void filebuffer::close(void)
{
	if(cache_memory != NULL) {
		free(cache_memory);
		cache_memory = NULL;
	}
	//変数の初期化
	cache_size = 0;
	internal_file_offset = 0;
	internal_file_size = 0;

	return;
}

unsigned long long filebuffer::getSize(void)
{
	//ファイルオープン
	HANDLE filehandle = CreateFile(input_filename, 
						SYNCHRONIZE|GENERIC_READ ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL,
						NULL
						);
	if (filehandle == INVALID_HANDLE_VALUE) {
		return 0;
	}

	//ファイルの長さを確認する。
	DWORD filesizelow;
	DWORD filesizehigh;

	filesizelow = GetFileSize(filehandle, &filesizehigh);
	if (filesizelow == -1) {
		CloseHandle(filehandle);
		return 0;
	}
	CloseHandle(filehandle);
	unsigned long long size = (filesizelow) | ((unsigned long long)filesizehigh<<32);

	return size;
}


