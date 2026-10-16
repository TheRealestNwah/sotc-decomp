extern void *isysGetThisSubThread(void);
extern char *B_00189DF4;

int existSoundBow(void)
{
    char *e;
    char *next;

    isysGetThisSubThread();
    for (e = B_00189DF4; e != 0; e = next) {
        next = *(char **)(e + 0xC0);
        if (*(int *)(e + 0x48) == 6) {
            if (*(short *)(e + 0xA0) == 0)
                return 1;
        }
    }
    return 0;
}
