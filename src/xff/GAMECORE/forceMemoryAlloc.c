extern int D_001798B0;
extern void *D_001798B4;
extern int rootPtn;
extern void iosFree(void *);
extern void *iosMallocAlign(void *, int, int);

void forceMemoryAlloc(void)
{
    if (D_001798B0 != 0) {
        if (D_001798B4 != 0) {
            iosFree(D_001798B4);
            D_001798B4 = 0;
        }
        D_001798B4 = iosMallocAlign(&rootPtn, D_001798B0 << 10, 4);
    } else {
        if (D_001798B4 != 0) {
            iosFree(D_001798B4);
            D_001798B4 = 0;
        }
    }
}
