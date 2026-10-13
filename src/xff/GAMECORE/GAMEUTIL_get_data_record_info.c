int GAMEUTIL_get_data_record_info(void *arg0, int arg1)
{
    if ((arg1 >= 0) && (arg1 < (*(int *)((char *)(arg0) + 0xC)))) {
        return (*(int *)((char *)(arg0) + 8)) + (arg1 * (*(int *)((char *)(arg0) + 0)));
    }
    return 0;
}
