extern int AddTwoWayLinkNext(int *, int *);
extern void *GetLayoutClass(void *);

#define NULL ((void *)0)
extern void DeleteTwoWayLink(void *);

void setObjGazeCtrlWork(void *arg0, void *arg1) {
    if ((*(int *)((char *)(arg0) + 0x40)) != 0) {
        (*(int *)((char *)(arg0) + 0x40)) = 0;
        DeleteTwoWayLink(arg0 + 0x34);
    }
    (*(void **)((char *)(arg0) + 0x30)) = arg1;
    if (arg1 != NULL) {
        AddTwoWayLinkNext(GetLayoutClass(arg1) + 0x118, arg0 + 0x34);
        (*(int *)((char *)(arg0) + 0x40)) = 1;
    }
}
