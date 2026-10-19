typedef struct Ptn Ptn;
typedef struct { int unknown; unsigned char *entries; unsigned char *bits; } SkipInfo;
extern Ptn rootPtn;
extern SkipInfo B_0015D4A0;
extern void *iosMallocAlign(Ptn *, int, int);
extern void *memset(void *, int, unsigned int);
void sheetMgrCreateStageIndexSkipInfo(int count)
{
    int bytes = (count - 1) / 8 + 1;
    B_0015D4A0.entries = iosMallocAlign(&rootPtn, count, 4);
    B_0015D4A0.bits = iosMallocAlign(&rootPtn, bytes, 4);
    memset(B_0015D4A0.entries, 0, count);
    memset(B_0015D4A0.bits, 0, bytes);
}
