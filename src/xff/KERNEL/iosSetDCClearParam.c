extern void func_000122B8(void *);

void iosSetDCClearParam(char *dc, int on, int r, int g, int b, int a)
{
    *(long *)(dc + 0x170) = (*(long *)(dc + 0x170) & ~1L) | (on & 1);
    dc[0x16C] = r;
    dc[0x16D] = g;
    dc[0x16E] = b;
    dc[0x16F] = a;
    func_000122B8(dc);
}
