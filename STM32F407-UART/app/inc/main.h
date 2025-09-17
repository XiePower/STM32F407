#ifndef __MAIN_H__
#define __MAIN_H__

#include <stddef.h>

void mem_init(void);//内存管理初始化
void *mem_malloc(size_t size);//内存分配
void mem_free(void *ptr);//内存释放

#endif /*__MAIN_H__*/
