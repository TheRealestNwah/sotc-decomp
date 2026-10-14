typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void CopyMultiMatrix(int, int, short);

void UpdateLayoutClassPastGeometry(void *arg0)
{
    *(*(s128 **)((char *)(arg0) + 0x138)) = *(*(s128 **)((char *)(arg0) + 0x134));
    (*(s128 *)((char *)(arg0) + 0xB0)) = (s128) (*(s128 *)((char *)(arg0) + 0xA0));
    if ((*(unsigned char *)((char *)(arg0) + 0x1BC)) & 0x20) {
        CopyMultiMatrix((*(int *)((char *)(arg0) + 0x168)), (*(int *)((char *)(arg0) + 0x164)), (*(short *)((char *)(arg0) + 0x1B4)));
    }
}
