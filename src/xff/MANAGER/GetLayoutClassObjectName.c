#define NULL ((void *)0)
extern void *modelGetName(int);
extern unsigned char RO_0013ED60[];

void *GetLayoutClassObjectName(void *arg0) {
    void **temp_v0_2;
    void *temp_v0;

    temp_v0_2 = (*(void ***)((char *)(arg0) + 0x144));
    if (temp_v0_2 != NULL) {
        temp_v0 = *temp_v0_2;
        if (temp_v0 != NULL) {
            return modelGetName((*(int *)((char *)(temp_v0) + 0x20)));
        }
    }
    return RO_0013ED60;
}
