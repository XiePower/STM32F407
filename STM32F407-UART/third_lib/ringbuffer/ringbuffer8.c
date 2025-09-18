#include <stdlib.h>
#include <string.h>
#include "ringbuffer8.h"

#define rbb_len rb->length
#define rbb_idx(x) (uint8_t *)rbb_buff + rbb_size *(x)
#define dat_idx(d, x) (uint8_t *)(d) + rbb_size *(x)

/*基于数组的环形缓冲区（ring buffer），用于存储uint8_t类型的数据*/

struct ringbuffer8
{
    uint32_t tail;    // 读取指针（下一个读取位置）
    uint32_t head;    // 写指针（下一个写入位置）
    uint32_t length;  // 缓冲区实际可用长度
    uint8_t buffer[]; // 柔性数组（数据存储区）
};

/*将给定的内存区域初始化为环形缓冲区*/
ringbuffer8_t rb8_new(uint8_t *buff, uint32_t length)
{
    ringbuffer8_t rb = (ringbuffer8_t)buff;
    rb->length = length - sizeof(struct ringbuffer8); // 可用长度=总长度-结构体头部大小

    return rb;
}

/*计算下一个写入位置（自动回绕到0）*/
static inline uint16_t next_head(ringbuffer8_t rb)
{
    return rb->head + 1 < rbb_len ? rb->head + 1 : 0;
}

//计算下一个读取位置（自动回绕到0）
static inline uint16_t next_tail(ringbuffer8_t rb)
{
    return rb->tail + 1 < rbb_len ? rb->tail + 1 : 0;
}

/*通过牺牲一个槽位判断环形缓冲区是否为空*/
bool rb8_empty(ringbuffer8_t rb)
{
    return rb->head == rb->tail;
}

/*通过牺牲一个槽位判断环形缓冲区是否为满*/
bool rb8_full(ringbuffer8_t rb)
{
    return next_head(rb) == rb->tail;
}

/*写入单个字节*/
bool rb8_put(ringbuffer8_t rb, uint8_t data)
{   //rb：指向环形缓冲区的指针，也就是结构体指针
    //rb->tail表示rb结构体中的tail变量，tail也是指针
    if (next_head(rb) == rb->tail)
        return false;//写入失败

    rb->buffer[rb->head] = data;
    rb->head = next_head(rb);
    return true;//写入成功
}

/*写入多个字节*/
bool rb8_puts(ringbuffer8_t rb, uint8_t *data, uint32_t size)
{
    bool ret = true;

    for (uint16_t i = 0; i < size && ret; i++)
    {
        ret = rb8_put(rb, data[i]);
    }

    return ret;
}

/*读取单个字节*/
bool rb8_get(ringbuffer8_t rb, uint8_t *data)
{
    if (rb->head == rb->tail)
        return false;

    *data = rb->buffer[rb->tail];
    rb->tail = next_tail(rb);

    return true;
}

/*读取多个字节*/
bool rb8_gets(ringbuffer8_t rb, uint8_t *data, uint32_t size)
{
    bool ret = true;

    for (uint16_t i = 0; i < size && ret; i++)
    {
        ret = rb8_get(rb, &data[i]);
    }

    return ret;
}
