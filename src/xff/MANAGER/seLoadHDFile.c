extern char rootPtn[];
extern char *sheetFileGetDataAdrs(int);
extern void *iosMallocAlign(void *, int, int);
extern int sndVabCreate(void);
extern void sheetFileRead(int, void *, int);
extern void sheetMgrDirectFileLoad(int, int, void *, int, int *);
extern void sndVabHDOpen(int, void *, int);

int seLoadHDFile(int file, int unused, int size)
{
    char *data = sheetFileGetDataAdrs(file);
    void *buf = iosMallocAlign(rootPtn, size, 16);
    int vab = sndVabCreate();

    if (file) {
        sheetFileRead(file, buf, size);
    } else {
        int status;

        sheetMgrDirectFileLoad(0, 0, buf, size, &status);
        while (status != 0xDEAF && status != 0xDEB0)
            ((void (*)(void))0)();
    }
    sndVabHDOpen(vab, buf, size);
    *(int *)(data + 0x1C) = vab;
    return vab;
}
