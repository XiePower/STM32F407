#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

int cmd_add(int argc, char *argv[])// 添加两个整数
{
    if (argc != 3)// 检查参数个数是否正确
    
    {
        shellWriteString(shellGetCurrent(), "parameter error\n");// 如果参数个数不正确，输出错误信息
        return -1; // 返回错误值
    }

    int a = atoi(argv[1]);// 将第一个参数转换为整数
    int b = atoi(argv[2]);// 将第二个参数转换为整数
    int c = a + b;
    //shellPrint(shellGetCurrent(), "The sum of %d and %d is %d\n", a, b, c);
    shellPrint(shellGetCurrent(), "%d + %d = %d\n", a, b, c);// 输出结果
    return 0;
}

// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, helloworld, cmd_helloworld, this is a helloworld command);
