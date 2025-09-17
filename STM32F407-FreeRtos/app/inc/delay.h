static void delay(void)
{
    for (unsigned int i = 0; i < 1000; i++)
    {
        for (unsigned int j = 0; j < 1000; j++)
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
}
