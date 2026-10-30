extern void gameModeCls(int mode);
extern void gameModeSet(int mode);

static void func_000ED330(char *p)
{
    while (*(int *)(p + 0x80) != 0) {
        if (*(int *)(p + 0x80) > 0) {
            gameModeCls(1);
            *(int *)(p + 0x80) -= 1;
        } else {
            gameModeSet(1);
            *(int *)(p + 0x80) += 1;
        }
    }
}
