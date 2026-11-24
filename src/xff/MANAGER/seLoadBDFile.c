extern void *DldSysUndefSymbol;
extern char *sheetFileGetDataAdrs(void *);
typedef struct { int start; int size; } SoundDefinition;
static void *func_000DCEF0(char *, SoundDefinition *, int, void *, int, int);

static inline void *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

void seLoadBDFile(void *sheet, int unused, int dest)
{
    char *adrs = sheetFileGetDataAdrs(sheet);

    func_000DCEF0(adrs, resourceData((unsigned int *)(adrs + 0x18)), dest, sheet, 0, 0);
}

typedef struct Partition Partition;
typedef struct { void *owner; int definition; } SoundEntry;
extern Partition rootPtn;
extern SoundEntry *B_001502C0;
extern int B_001502C4;
extern int B_001502C8;
extern int B_001502CC;
extern int B_001502D0;
extern int B_001502D4;
extern void *B_001502D8;
extern void *B_001502DC;
extern int func_000DD6C0(void);
extern int D_000DD730(void);
extern void iosJumpRecoverPoint(const void *, ...);
extern void *iosMallocAlign(Partition *, int, int);
extern void iosFree(void *);
extern void sndBDOpen(void *, void *, void *, int, int);
extern void sndVabHDClose(void *);
extern void sndVabDelete(void *);

static inline int allocSpu(SoundDefinition *bd, int *slot, void *hd)
{
    SoundEntry *e = 0;
    SoundEntry *f;
    int start;
    int end;
    int i;

    for (i = 0; i < B_001502C4; i++) {
        e = &B_001502C0[i];
        *slot = (int)e;
        if (e->definition == (int)bd)
            goto found;
    }
    iosJumpRecoverPoint("chkAllocSpuAdrs: layout info\244\254\270\253\311\325\244\253\244\352\244\336\244\273\244\363\244\307\244\267\244\277 %p\n", bd);
found:
    if (e->owner != 0)
        return 1;
    start = ((SoundDefinition *)e->definition)->start;
    end = start + (((SoundDefinition *)e->definition)->size << 10);
    for (i = 0; i < B_001502C4; i++) {
        f = &B_001502C0[i];
        if (f->owner != 0 && ((SoundDefinition *)f->definition)->start < end
            && start < ((SoundDefinition *)f->definition)->start + (((SoundDefinition *)f->definition)->size << 10))
            return 1;
    }
    e->owner = hd;
    return 0;
}

static void *func_000DCEF0(char *hd, SoundDefinition *bd, int size, void *flag, int t0, int t1)
{
    char *snd = *(char **)(hd + 0x1C);
    int *slot;
    int data;
    int addr;

    if (snd == 0)
        iosJumpRecoverPoint("_seLoadBDFile: hd file\244\254\300\350\244\313\275\351\264\374\262\275\244\265\244\354\244\306\244\244\244\336\244\273\244\363\n");
    if (flag != 0) {
        B_001502D8 = flag;
    } else {
        B_001502CC = t0;
        B_001502D0 = 0;
        B_001502D4 = t1;
    }
    B_001502C8 = size;
    slot = (int *)(snd + 0x18);
    data = bd->start;
    *slot = 0;
    if ((bd->size << 10) < size)
        addr = 0;
    else
        addr = allocSpu(bd, slot, hd) == 0 ? data : 0;
    if (addr != 0) {
        *(int *)(snd + 0x10) = addr;
        *(int *)(snd + 0x14) = size;
        B_001502DC = iosMallocAlign(&rootPtn, 0x10000, 0x40);
        if (B_001502DC == 0)
            iosJumpRecoverPoint("_seLoadBDFile: ee\244\313\305\276\301\367\316\316\260\350\244\254\263\316\312\335\244\307\244\255\244\336\244\273\244\363\244\307\244\267\244\277.\n");
        {
            /* The Original forms &B_001502DC, then sets $a0, loads $a2 and sets $t0 in that order. */
            void *fn = flag != 0 ? (void *)func_000DD6C0 : (void *)D_000DD730;
            register char *s __asm__("$4") = snd;
            register void *bb __asm__("$6");
            register int tt __asm__("$8");
            __asm__ __volatile__("" : "+r"(s) : "r"(&B_001502DC));
            bb = B_001502DC;
            __asm__ __volatile__("" : "+r"(bb));
            tt = t1;
            sndBDOpen(s, fn, bb, 0x10000, tt);
        }
        iosFree(B_001502DC);
        return snd;
    } else {
        void *p = *(void **)(snd + 0xC);
        sndVabHDClose(snd);
        iosFree(p);
        sndVabDelete(snd);
        return 0;
    }
}
