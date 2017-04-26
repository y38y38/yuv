// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������

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



