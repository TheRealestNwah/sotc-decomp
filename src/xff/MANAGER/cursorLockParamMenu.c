#define NULL ((void *)0)
void cursorLockParamMenu(void *arg0, int arg1) {
    void *temp_a0;
    void *temp_a1;

    if (arg0 != NULL) {
        temp_a0 = (*(void **)((char *)(arg0) + 0x2C));
        if (temp_a0 != NULL) {
            temp_a1 = (*(void **)((char *)(temp_a0) + 4));
            (*(long *)((char *)(temp_a1) + 0x1B8)) = (long) (((*(long *)((char *)(temp_a1) + 0x1B8)) & ~0x80) | ((arg1 & 1) << 7));
        }
    }
}
