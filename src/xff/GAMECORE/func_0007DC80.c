extern int GAMEUTIL_get_motion_kind(void *obj);

static unsigned int func_0007DC80(void *obj)
{
    char *m = (char *)GAMEUTIL_get_motion_kind(obj);
    if (m == 0) {
        return 0;
    }
    return (*(unsigned int *)(m + 0x6C) >> 15) & 7;
}
