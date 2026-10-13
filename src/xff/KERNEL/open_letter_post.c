void open_letter_post(void *arg0)
{
    (*(int *)((char *)(arg0) + 0xC)) = 0;
    (*(int *)((char *)(arg0) + 0x10)) = (int) (*(int *)((char *)(arg0) + 4));
}
