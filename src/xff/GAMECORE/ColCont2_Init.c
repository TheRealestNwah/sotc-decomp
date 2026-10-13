extern void InitTwoWayLink(void *, int);

void ColCont2_Init(void *arg0)
{
    (*(long *)((char *)(arg0) + 0)) = 0;
    (*(long *)((char *)(arg0) + 8)) = 0;
    (*(int *)((char *)(arg0) + 0x10)) = 0;
    (*(int *)((char *)(arg0) + 0x24)) = 0;
    InitTwoWayLink(arg0 + 0x14, arg0 + 0x20);
    (*(int *)((char *)(arg0) + 0x20)) = 0;
}
