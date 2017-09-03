#include <stdio.h>
#include "enc_g711.h"
#include "enc_g711_debug.h"
static FUNC_POINTER func_;
void EncG711Send(unsigned long id, void* address, unsigned long size)
{
	debug_g711_printf("%s start\n", __FUNCTION__);
	func_(id);
	debug_g711_printf("%s end\n", __FUNCTION__);
	return;
}
void EncG711RegisterFunc(FUNC_POINTER func_ptr)
{
	debug_g711_printf("%s start\n", __FUNCTION__);
	debug_g711_printf("func_ptr = 0x%x\n", (unsigned int)func_ptr);
	func_ = func_ptr;
	debug_g711_printf("%s end\n", __FUNCTION__);
	return;
}

