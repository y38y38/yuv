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
	//size は今すぐに読みたいサイズ。
	int cache_update(unsigned long long offset, unsigned long size, unsigned long *result_read_size);
	int direct_read(unsigned char *write_buffer,unsigned long long offset, unsigned long size, unsigned long *result_raed_size);

	//static DWORD WINAPI ThreadFunc(LPVOID vdParam);

	//キャッシュ用のバッファポインタ
	unsigned char *cache_memory;

	//キャッシュ用のバッファサイズ。
	unsigned long cache_size;

	//キャッシュ用バッファの先頭のファイルの位置
	//キャッシュすると更新される。
	unsigned long long internal_file_offset;

	//キャッシュ用バッファ内に、ファイル内のデータサイズ。
	//通常は、buffer_sizeと同じだけど、ファイルのお尻に
	//行くとbuffer_sizeより小さくなる。
	unsigned long internal_file_size;
	
	//ファイルネーム
	TCHAR input_filename[1024];

};

#endif
