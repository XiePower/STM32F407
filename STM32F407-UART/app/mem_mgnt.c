#include <stdbool.h>
#include <stdint.h>
#include "tlsf.h"

static uint8_t dyl_mem_pool[64*1024];//开辟一个动态内存池
static tlsf_t tlsf;// 定义一个TLSF内存分配器

/**
 * @brief 你需要先分配一块原始内存（如通过 malloc 或静态数组）作为内存池的基础

TLSF 会在这块内存上建立管理结构，因此可用内存会比原始内存略小

确保原始内存块的对齐符合 TLSF 的要求（通常至少是 4 字节对齐）

使用 tlsf_malloc 和 tlsf_free 时需要使用相同的 tlsf_t 实例
 * 
 */

/**
 * @brief 使用TLSF内存分配器创建和管理内存池
 * 
 */
void mem_init(void)
{
	tlsf = tlsf_create_with_pool(dyl_mem_pool, sizeof(dyl_mem_pool));//创建TSLF内存池
	//错误处理，如果创建失败则进入死循环
	if(tlsf == NULL)//检测内存池是否创建成功
	{
		while(1);//无限循环，表示严重错误
	}    
}

void *mem_malloc(size_t size)// 分配内存
{
    return tlsf_malloc(tlsf, size);// 使用TLSF分配内存
}

void mem_free(void *ptr)// 释放内存
{
    tlsf_free(tlsf, ptr);// 使用TLSF释放内存
}
