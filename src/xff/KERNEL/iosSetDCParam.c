extern void func_000122B8(void *);

void iosSetDCParam(char *dc, int a, int b, int c, int d)
{
    *(int *)(dc + 0x160) = a;
    *(int *)(dc + 0x164) = b;
    *(short *)(dc + 0x168) = c;
    *(short *)(dc + 0x16A) = d;
    func_000122B8(dc);
}
