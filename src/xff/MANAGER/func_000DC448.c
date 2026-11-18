/* Parked: 4 diffs (v0/v1 swapped between the free-list head and the list-loop pointers). */
typedef struct { int pad; } Ptn;

typedef struct AdpcmBuf {
    char pad0[0x14];
    struct AdpcmBuf *next;
} AdpcmBuf;

typedef struct {
    char pad0[0x70];
    void *iopBuf;
    void *iopEnd;
    int spuAddr;
    char pad7C[0x84 - 0x7C];
    AdpcmBuf bufs[20];
    AdpcmBuf *free;
    int unk268;
    int unk26C;
    int unk270;
    char pad274[0x280 - 0x274];
    char work[0x560 - 0x280];
} AdpcmSlot;

extern void *memset(void *, int, int);
extern void Sg2ExStAdpcmWorkClear(void *, int);
extern void *sceSifAllocSysMemory(int, int, void *);
extern void iosJumpRecoverPoint(char *);
extern void LoaderSysEntryExternalIopMemoryList(void *);
extern void *iosMallocAlign(Ptn *, int, int);
extern void iosEE2IopRequest(void *, void *, int, int *);
extern int iosEE2IopEndChk(int);
extern void iosFree(void *);
extern Ptn rootPtn;
extern int D_00139BE0;
extern int D_00139BE4;
extern AdpcmSlot B_0014E898[3];

#ifdef NONMATCHING
static void func_000DC448(void)
{
    int i;
    int j;
    int spu;
    AdpcmSlot *s;
    void *tmp;
    int id;

    memset(B_0014E898, 0, sizeof(B_0014E898));
    spu = 0x1E0000;
    for (i = 0; i < 3; i++) {
        s = &B_0014E898[i];
        Sg2ExStAdpcmWorkClear(s->work, 0);
        s->iopBuf = sceSifAllocSysMemory(0, D_00139BE4, 0);
        if (s->iopBuf == 0)
            iosJumpRecoverPoint("adpcmFileInit: iop buf not allocate\n");
        s->spuAddr = spu;
        s->iopEnd = (char *)s->iopBuf + D_00139BE4;
        LoaderSysEntryExternalIopMemoryList(s->iopBuf);
        s->free = s->bufs;
        s->unk26C = 0;
        s->unk268 = 0;
        s->unk270 = 0;
        for (j = 0; j < 19; j++)
            s->bufs[j].next = &s->bufs[j + 1];
        s->bufs[j].next = 0;
        if (D_00139BE0 != 0) {
            tmp = iosMallocAlign(&rootPtn, D_00139BE4, 16);
            memset(tmp, 0, D_00139BE4);
            iosEE2IopRequest(tmp, s->iopBuf, D_00139BE4, &id);
            while (iosEE2IopEndChk(id) == 0)
                ;
            iosFree(tmp);
        }
        spu += 0x8000;
    }
}
#endif
