extern void DeleteTwoWayLink(int);

void ColCont2_Release(void *arg0)
{
    (*(long *)((char *)(arg0) + 8)) = 0;
    (*(long *)((char *)(arg0) + 0)) = 0;
    (*(int *)((char *)(arg0) + 0x10)) = 0;
    (*(int *)((char *)(arg0) + 0x24)) = 0;
    if ((*(int *)((char *)(arg0) + 0x20)) != 0) {
        (*(int *)((char *)(arg0) + 0x20)) = 0;
        DeleteTwoWayLink(arg0 + 0x14);
    }
}
