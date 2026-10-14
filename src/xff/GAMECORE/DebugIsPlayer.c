#define NULL ((void *)0)
extern void *GetLayoutClass();
extern int strcmp(int, void *);
extern unsigned char RO_0017C110[1];

int DebugIsPlayer(void)
{
    void *temp_v0;

    temp_v0 = GetLayoutClass();
    if ((temp_v0 != NULL) && (strcmp((*(int *)((char *)(temp_v0) + 0x130)), &RO_0017C110) == 0)) {
        return 1;
    }
    return 0;
}
