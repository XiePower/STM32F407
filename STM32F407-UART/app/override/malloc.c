#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "main.h"

void *malloc(size_t size)// 分配内存
{
    return mem_malloc(size);// 使用自定义的内存分配函数
}

void free(void* p)
{
    mem_free(p);
}
