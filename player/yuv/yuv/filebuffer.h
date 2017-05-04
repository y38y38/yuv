#ifndef _FILEBUFFER_
#define _FILEBUFFER_

class filebuffer {
public:
	filebuffer(void);
	~filebuffer(void);
	int create(TCHAR *filename, unsigned long buffer_size);

	int read(unsigned char *buffer, unsigned long long offset, unsigned long size, unsigned long *result_read_size);
	void close(void);
	unsigned long long getSize(void);

#if CACHE_THREAD_ON
	void thread_run();	
	static void EntryPoint(LPVOID data)
	{
		buffer *buffer_test = (buffer*)data;
		buffer_test->thread_run();
	}
#else

#endif

private:
	//size �͍������ɓǂ݂����T�C�Y�B
	int cache_update(unsigned long long offset, unsigned long size, unsigned long *result_read_size);
	int direct_read(unsigned char *write_buffer,unsigned long long offset, unsigned long size, unsigned long *result_raed_size);

	//static DWORD WINAPI ThreadFunc(LPVOID vdParam);

	//�L���b�V���p�̃o�b�t�@�|�C���^
	unsigned char *cache_memory;

	//�L���b�V���p�̃o�b�t�@�T�C�Y�B
	unsigned long cache_size;

	//�L���b�V���p�o�b�t�@�̐擪�̃t�@�C���̈ʒu
	//�L���b�V������ƍX�V�����B
	unsigned long long internal_file_offset;

	//�L���b�V���p�o�b�t�@���ɁA�t�@�C�����̃f�[�^�T�C�Y�B
	//�ʏ�́Abuffer_size�Ɠ��������ǁA�t�@�C���̂��K��
	//�s����buffer_size��菬�����Ȃ�B
	unsigned long internal_file_size;
	
	//�t�@�C���l�[��
	TCHAR input_filename[1024];

};

#endif
