typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern void sheetFileRead(void *, void *, int);
extern void kSetTex(void *);

void *loadCdNfbFile(void *f, int unused, int size)
{
    void *b = iosMallocAlign(&rootPtn, size, 16);
    if (b != 0) {
        sheetFileRead(f, b, size);
        kSetTex(b);
    }
    return b;
}
