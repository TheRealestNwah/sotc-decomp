extern char *GAMEUTIL_get_motion_kind(void *);

static void func_0007C1C0(void *c, char *o)
{
    char *m;

    if (*(int *)(o + 0xD8C) == 1) {
        m = GAMEUTIL_get_motion_kind(c);
        if (!m || *(int *)(m + 0x90) != 0x31)
            *(int *)(o + 0xD8C) = 0;
    }
}
