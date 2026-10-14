#define NULL ((void *)0)
extern void *D_001303E0;

void fsEffectSetParam(void *arg0) {
    if ((arg0 != NULL) && ((D_001303E0 == NULL) || (((*(int *)((char *)(arg0) + 4)) * 0x10) >= ((*(int *)((char *)(D_001303E0) + 4)) * 0x10)))) {
        D_001303E0 = arg0;
    }
}
