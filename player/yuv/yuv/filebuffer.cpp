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
	//�t�@�C���I�[�v��
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

	//�t�@�C���V�[�N
	DWORD now_position;
	LONG setoffset;
	LONG setoffsethigh;
	DWORD dwError;
		
	//�I�t�Z�b�g��32bit�ɕ���
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
	//�t�@�C���V�[�N�����܂�


	//�t�@�C�����[�h
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
		//�ǂݎ�萬��
		*result_read_size = readsize;
	}
	CloseHandle(filehandle);

	return 1;
}

#if CACHE_THREAD_ON
#if 1
void filebuffer::thread_run(void)
{
	//�X���b�h���ōs������������B
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

	//�ȉ����X���b�h�Ɉړ�����B
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

	//�܂��͂����ɕK�v�ȕ������ǂݏo���āA���Ƃ͕ʃX���b�h�œǂݍ��ށB�����[�B
	int result = direct_read(cache_memory, offset, size, &readsize);
	if (result < 0) {
		return -1;
	}
	//internal_file_size�͂��܂����B�B�B
	internal_file_size = cache_size;
	internal_file_offset = offset;

	//�ȉ����X���b�h�Ɉړ�����B
	if (( cache_size - size ) > 0) {
		DWORD dwID;
		CreateThread(NULL , 0 , (LPTHREAD_START_ROUTINE)buffer::EntryPoint , (LPVOID)this , 0 , &dwID);
	}
	return internal_file_size;
#else
	unsigned long readsize;

	//�܂��͂����ɕK�v�ȕ������ǂݏo���āA���Ƃ͕ʃX���b�h�œǂݍ��ށB�����[�B
	int result = direct_read(cache_memory, offset, cache_size, &readsize);
	if (result < 0) {
		return -1;
	}
	internal_file_size = readsize;
	internal_file_offset = offset;
	return internal_file_size;

#endif
}


//�L���b�V���T�C�Y��0�̏ꍇ���l���āB
int filebuffer::create(TCHAR *filename, unsigned long memory_size)
{
	//�ϐ��̏�����
	cache_memory = NULL;
	cache_size = 0;
	internal_file_offset = 0;
	internal_file_size = 0;

	//�t�@�C�����̕ۑ�
	_tcsncpy_s(input_filename, filename, 1024);

	if (memory_size == 0) {
		//���̏ꍇ��direct�Ŗ���ǂ�
		return 0;
	}

	//�L���b�V���������̎擾
	cache_memory = (unsigned char *)malloc(memory_size);
	if (cache_memory == NULL) {
		return -1;
	}
	//�L���b�V���T�C�Y��ۑ��B
	cache_size = memory_size;

//#if CACHE_THREAD_ON
#if 0
	DWORD dwID;
	CreateThread(NULL , 0 , (LPTHREAD_START_ROUTINE)buffer::EntryPoint , (LPVOID)this , 0 , &dwID);

#else
	//create�������́A�t�@�C���̐擪���L���b�V������B
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

	//���[�h����T�C�Y���A�L���b�V���T�C�Y���傫�����m�F
	if (size > cache_size) {
		//���[�h����T�C�Y���L���b�V�����傫���ꍇ�́A�t�@�C������
		//���ڃ��[�h���āA�o�b�t�@�Ƀ��C�g����B
		result = direct_read(buffer, offset, size, result_read_size);
		if (result < 0) {
			return -1;
		}
	} else {
		//�L���b�V����HIT���邩�m�F
		if (offset >= internal_file_offset) {
			//�I�t�Z�b�g�̓L���b�V�����ɂ���B
			
			if ((offset + size) <= (internal_file_offset + internal_file_size)) {
				//���[�h�������Ō�̃f�[�^���L���b�V�����ɂ���B
				//HIT
				*result_read_size = size;
			} else {
				//���[�h�������Ō�̃f�[�^���L���b�V���̊O�Ȃ̂ŁA�L���V������蒼���B
				result = cache_update(offset, size, result_read_size);
				if (result < 0) {
					return -1;
				} else if (result == 0) {
					//end of file
					*result_read_size = 0;
					return 0;
				} else {
					//�L���b�V���Ƀf�[�^�ړ������B
					//���ۂɃR�s�[����T�C�Y���X�V�B
					*result_read_size = size;
				}
			}
		} else {
			//���[�h�������擪�̃f�[�^���L���b�V���̊O�Ȃ̂ŁA�L���V������蒼���B
			result = cache_update(offset, size, result_read_size);
			if (result < 0) {
				return -1;
			} else if (result == 0) {
				//end of file
				return 0;
			} else {
				//�L���b�V���Ƀf�[�^�ړ������B
				//���ۂɃR�s�[����T�C�Y���X�V�B
				*result_read_size = size;
			}
		}

		//���[�h�������f�[�^�̓L���V�����ɂ���B
		//size�łȂ�readsize���g�p����̂́A�Ⴆ�΁A�w�肳�ꂽ�T�C�Y���t�@�C�����Ƀf�[�^���Ȃ������ꍇ��

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
	//�ϐ��̏�����
	cache_size = 0;
	internal_file_offset = 0;
	internal_file_size = 0;

	return;
}

unsigned long long filebuffer::getSize(void)
{
	//�t�@�C���I�[�v��
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

	//�t�@�C���̒������m�F����B
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


