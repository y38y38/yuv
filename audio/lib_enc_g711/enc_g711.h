#ifndef _ENCG711_
#define _ENCG711_


void EncG711Send(unsigned long id, void* address, unsigned long size);
typedef void (* FUNC_POINTER)(unsigned long id);
void EncG711RegisterFunc(FUNC_POINTER func_ptr);
#endif /* _ENCG711_ */
