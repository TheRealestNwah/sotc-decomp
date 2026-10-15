typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern char *sheetFileGetDataAdrs(void *);
extern void sheetFileRead(void *, void *, int);

int adpcmLoadStsFile(void *f, int unused, int size)
{
    void *b = iosMallocAlign(&rootPtn, size, 16);
    char *d = sheetFileGetDataAdrs(f);
    sheetFileRead(f, b, size);
    *(void **)(d + 0x10) = b;
    return 0;
}
