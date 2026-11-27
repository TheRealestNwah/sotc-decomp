/* Parked: 3 words differ. Register pins on len ($s5), res ($s4) and a5 ($s7)
 * give the Original's callee-saved assignment, but the first use of a5
 * still reads $t1 instead of the pinned copy, and the obj->info store is
 * scheduled after the mask's ori. The 3 nops in the last loop come from
 * the assembler's r5900 short-loop fix, not from source. */
#ifdef NONMATCHING
typedef struct {
    char pad0[8];
    int size;
    char padC[4];
    int type;
    int x14;
    int x18;
    char pad1C[4];
} Sect;

typedef struct {
    char pad0[0xC];
    unsigned char xC;
    char padD[3];
    int x10;
    char pad14[8];
    int x1C;
    char pad20[4];
    int x24;
    void *x28;
    char pad2C[4];
    Sect *sects;
    char pad34[8];
    char *x3C;
    int nsects;
    char pad44[0x20];
    int x64;
} ModInfo;

typedef struct {
    char pad0[0x1C];
    ModInfo *info;
    int x20;
    char pad24[8];
    unsigned int flags;
} ModObj;

extern void *B_000543A0;
extern char symbolDefModuleGroup[];
extern void *iosCreatePartition(int, int);
extern void *iosMallocAlign(void *, int, int);
extern void *memcpy(void *, const void *, unsigned int);
extern void RelocateElfInfoHeader(ModInfo *, void *, void *, int);
extern void LoaderSysRelocateOnlineElfInfo(ModInfo *, void *, void *, int, void *);
extern void DecodeSection(ModInfo *, void *, void *, void *);
extern void RelocateSelfSymbol(ModInfo *, int);
extern void RelocateCode(ModInfo *);
extern void isysAddGroupWithLinkParam(ModObj *, char[], int, int);
extern void func_00007968(ModObj *, int);
extern void *func_0000A2C0(ModInfo *);
extern void func_0000A078(void);
extern void *T_0000A0A0(int);

void *func_00007B78(ModInfo *info, ModObj *obj, int heap, void *a3, void *a4, int a5_, void *a6, int a7)
{
    register int a5 asm("$23") = a5_;
    int ok = 0;
    int total;
    int k;
    int nsym;
    register int len asm("$21");
    register int *res asm("$20");

    if (a7 != 0) {
        info->x3C = (char *)info + info->x64;
        ok = info->x1C == 0;
    }
    if (ok) {
        RelocateElfInfoHeader(info, a3, a4, a5);
        len = 0;
        {
            Sect *s = info->sects + 1;
            int n = info->nsects - 2;
            total = 0;
            while (n != -1) {
                unsigned int t = s->type;
                s->x14 = 1;
                switch (t) {
                case 1:
                case 8:
                case 0x7FFFF420:
                    total += s->size + 0x33;
                    break;
                }
                n--;
                s++;
            }
        }
        k = info->xC + 1;
        if (info->xC == 0)
            { __asm__ __volatile__(""); k = 2; }
        nsym = info->x24 - info->x1C - k;
        if (nsym != 0) {
            len = info->x24 << 4;
            total += len;
        }
        B_000543A0 = iosCreatePartition(a7, total + 0x3B);
        res = iosMallocAlign(B_000543A0, 8, 4);
        if (nsym != 0) {
            void *p = iosMallocAlign(B_000543A0, len, 4);
            memcpy(p, info->x28, len);
            info->x28 = p;
        }
        DecodeSection(info, func_0000A078, T_0000A0A0, a6);
        RelocateSelfSymbol(info, a5);
        RelocateCode(info);
        if (nsym != 0) {
            obj->info = info;
            obj->flags &= ~0x20000000;
            obj->x20 = info->x10;
            func_00007968(obj, heap);
            isysAddGroupWithLinkParam(obj, symbolDefModuleGroup, 0, 0);
        }
        {
            int n = info->nsects - 2;
            Sect *s = info->sects + 1;
            while (n != -1) {
                n--;
                s->x18 = 0;
                s++;
            }
        }
        res[0] = info->x10;
        res[1] = (int)B_000543A0;
        func_0000A2C0(info);
        return res;
    }
    LoaderSysRelocateOnlineElfInfo(info, a3, a4, a5, a6);
    return 0;
}
#endif
