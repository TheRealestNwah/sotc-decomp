

#define NULL ((void *)0)
void texGetSize(void *arg0, int *arg1, int *arg2) {
    void *temp_a3;

    temp_a3 = (*(void **)((char *)(arg0) + 0x20));
    if (temp_a3 != NULL) {
        if ((*(int *)((char *)(temp_a3) + 0)) == 0x324F544E) {
            *arg1 = 1 << ((*(unsigned short *)((char *)(temp_a3) + 0x1E)) & 0xF);
            *arg2 = 1 << (((unsigned int) (*(unsigned int *)((char *)(temp_a3) + 0x1C)) >> 0x14) & 0xF);
        }
    } else {
        *arg2 = 0;
        *arg1 = 0;
    }
}
