typedef struct {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

extern int LoaderSysPrintf(const char *format, ...);
extern unsigned int strlen(const char *s);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern int strcmp(const char *a, const char *b);
extern void FlushCache(int mode);
extern void sceSifInitRpc(unsigned int mode);
extern int sceSifInitIopHeap(void);
extern void *sceSifAllocSysMemory(int type, int size, void *addr);
extern int sceSifFreeSysMemory(void *addr);
extern unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
extern int sceSifDmaStat(unsigned int id);
extern int sceSifLoadModuleBuffer(void *ptr, int args, const char *argp);
extern char D_00136900[];
extern char D_00136948[];
extern char D_00136980[];
extern char D_001369C0[];
extern int D_0013A008;
extern char D_0013CB90[][16];

static inline int LoadModuleBuffer(void *buf, int size, int args, const char *argp) {
    sceSifDmaData dma;
    void *iop;
    unsigned int id;
    int ret;

    size = (size + 3) & ~3;
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    iop = sceSifAllocSysMemory(1, size, 0);
    LoaderSysPrintf(D_00136900, iop, size);
    FlushCache(0);
    dma.data = (unsigned int)buf;
    dma.addr = (unsigned int)iop;
    dma.size = size;
    dma.mode = 0;
    id = sceSifSetDma(&dma, 1);
    while (sceSifDmaStat(id) >= 0) {
    }
    LoaderSysPrintf(D_00136948);
    ret = sceSifLoadModuleBuffer(iop, args, argp);
    sceSifFreeSysMemory(iop);
    return ret;
}

static inline char *AddIopIdentifier(const char *name) {
    LoaderSysPrintf(D_00136980, name, D_0013A008);
    return strncpy(D_0013CB90[D_0013A008++], name, strlen(name));
}

static inline int FindIopIdentifier(const char *name) {
    int i;

    for (i = 0; i < D_0013A008; i++) {
        if (strcmp(D_0013CB90[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int LoaderSysLoadIopModuleFromEEBuffer(const char *name, void *buf, int size, int args, const char *argp) {
    int found;
    int ret;

    if (name != 0) {
        found = FindIopIdentifier(name);
        if (found < 0) {
            ret = LoadModuleBuffer(buf, size, args, argp);
            if (ret >= 0) {
                AddIopIdentifier(name);
            }
            return ret;
        }
        LoaderSysPrintf(D_001369C0, name, found);
        return 0;
    }
    return LoadModuleBuffer(buf, size, args, argp);
}
