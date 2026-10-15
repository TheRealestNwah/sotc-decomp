typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern void sheetFileRead(void *, void *, int);

void *loadPathData(void *f, void *b, int size)
{
    void *p = iosMallocAlign(&rootPtn, size, 16);
    sheetFileRead(f, p, size);
    return p;
}
