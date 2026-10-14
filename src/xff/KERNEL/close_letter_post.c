void close_letter_post(char *p)
{
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x10) = 0;
}
