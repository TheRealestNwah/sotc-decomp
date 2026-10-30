typedef struct { unsigned long long data[12]; } sceGsLoadImage;

extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void *memset(void *, int, unsigned int);
extern int sceGsSetDefLoadImage(sceGsLoadImage *, short, short, short, short, short, short, short);
extern void FlushCache(int);
extern int sceGsExecLoadImage(sceGsLoadImage *, void *);
extern int sceGsSyncPath(int, unsigned short);

void ClearVRAM(void)
{
    sceGsLoadImage load;
    void *image;
    int i;
    int dbp;

    image = iosMallocAlign(rootPtn, 0x40000, 0x10);
    dbp = 0;
    memset(image, 0, 4);
    for (i = 0; i < 16; i++) {
        sceGsSetDefLoadImage(&load, dbp, 4, 0, 0, 0, 0x100, 0x100);
        dbp += 0x400;
        FlushCache(0);
        sceGsExecLoadImage(&load, image);
        sceGsSyncPath(0, 0);
    }
    iosFree(image);
}
