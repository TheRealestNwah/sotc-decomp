extern int AddTwoWayLinkNext(int *, int *);
extern void *GetLayoutClass(void *);
extern void InitTwoWayLink(char *, int);

void EntryCollisionFinder(void *arg0, void *arg1, int arg2) {
    int temp_a0;
    signed char *temp_s0;
    void *temp_v0;

    temp_a0 = (*(int *)((char *)(arg0) + 0));
    if (temp_a0 < (*(int *)((char *)(arg0) + 4))) {
        temp_v0 = (*(int *)((char *)(arg0) + 0xC)) + (temp_a0 * 8);
        temp_s0 = (*(int *)((char *)(arg0) + 0x10)) + (temp_a0 * 0xC);
        (*(int *)((char *)(temp_v0) + 4)) = arg2;
        (*(void **)((char *)(temp_v0) + 0)) = arg1;
        InitTwoWayLink(temp_s0, (int) temp_v0);
        AddTwoWayLinkNext((*(int *)((char *)(GetLayoutClass(arg1)) + 0x174)) + 0x10, (int *) temp_s0);
    }
    (*(int *)((char *)(arg0) + 0)) = (int) ((*(int *)((char *)(arg0) + 0)) + 1);
}
