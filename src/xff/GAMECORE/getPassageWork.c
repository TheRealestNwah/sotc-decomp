#define NULL ((void *)0)
void *getPassageWork(void *arg0, int arg1) {
    if ((arg1 < 0x14) && ((unsigned int) arg1 < (unsigned int) (*(unsigned int *)((char *)(arg0) + 0x380)))) {
        return arg0 + (arg1 << 5) + 0x100;
    }
    return NULL;
}
