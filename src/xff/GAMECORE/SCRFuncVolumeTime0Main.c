typedef int s128 __attribute__((mode(TI)));

extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, s128 *);

void SCRFuncVolumeTime0Main(void *a, int b, int c, int d, int e, int f, unsigned int *h)
{
    char buf[0x60];
    char *w = getSCRDataCtrlWork(a);
    s128 pos = **(s128 **)(*(char **)(w + 0x407C) + 0x134);
unsigned int v = *h;
int voff = v & 0x3FFFF;
char *t = voff != 0 ? *(char **)((char *)h - voff) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    if (p != 0 && CheckPositionInsideOfJudgeVolumeObject(buf, a, h, &pos))
        *(float *)(w + 0x40AC) += *(float *)(gcGlobalVar + 0x190);
    else
        *(int *)(w + 0x40AC) = 0;
}
