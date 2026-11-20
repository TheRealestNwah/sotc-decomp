#ifdef NONMATCHING
/* Parked attempt: 1 differing word. Called from AddCollMan.c. */
typedef struct FogColMan {
    char pad0[0x90];
    int flags;
    char pad94[4];
    char g98[4];
    char g9C[4];
    char gA0[4];
} FogColMan;

typedef struct {
    int hash;
    char pad4[0x14];
    int flags;
    char pad1C[0x44];
} FsEntry;

extern FogColMan B_00148A40;
extern int DldSysUndefSymbol;
extern char SH_FsEffectDEFAULT[];
extern int func_00071738(unsigned char *, char *, void *, int);
extern char *strstr(const char *, const char *);
extern int strcmp(const char *, const char *);
extern int MakeStrHashValue(const char *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

int func_00071AF0(unsigned char *w, char *a, void *b, int pass, void *obj, void *unused)
{
    FogColMan *man = &B_00148A40;
    int ret = 0;

    if (*(int *)(w + 0x40) == 0) {
        char *s;
        int name;
        char *p;
        int i;

        if (func_00071738(w, a, b, pass) == 0)
            goto end;
        *(int *)(w + 0x40) |= 0x100;
        name = *(int *)(a + 4);
        *(int *)(w + 0x44) = name;
        s = strstr((char *)name, "eff_");
        p = 0;
        *(int *)(w + 0x7C) = 0;
        if (s != 0)
            p = s + 4;
        *(int *)(w + 0x78) = -1;
        *(int *)(w + 0x80) = 1;
        if (p != 0) {
            char *d = (char *)DldSysUndefSymbol != SH_FsEffectDEFAULT ? SH_FsEffectDEFAULT : 0;
            int n = *(int *)(d + 0xC);
            FsEntry *list = *(FsEntry **)(d + 0x10);
            FsEntry *e;

            i = 0;
            if (i < n) {
                do {
                    e = &list[i];
                    if (e->hash == MakeStrHashValue(p)) {
                        *(int *)(w + 0x78) = i;
                        if (e->flags & 3)
                            *(int *)(w + 0x7C) |= 2;
                        break;
                    }
                    i++;
                } while (i < n);
            }
        }
        isysAddGroupWithLinkParam(obj, man->g9C, 0, 0);
        _isysDeleteGroup(obj, man->g98, 0);
        ret = 1;
    } else if (*(int *)(w + 0x40) & 0x100) {
        int flags;
        int mask;
        int nf;
        float v[4] __attribute__((aligned(16)));
        float f;

        if (strcmp(*(char **)(w + 0x44), *(char **)(a + 4)) != 0)
            goto end;
        if (func_00071738(w, a, b, pass) == 0)
            goto end;
        flags = *(int *)(w + 0x40);
        mask = (flags & 0xC) ? 0x1F0 : 0x1D0;
        if ((flags & mask) == mask) {
        f = *(float *)(w + 0x30);
        if (f < *(float *)(w + 0x34))
            f = *(float *)(w + 0x34);
        if (f < *(float *)(w + 0x38))
            f = *(float *)(w + 0x38);
        v[0] = f;
        v[1] = f;
        v[2] = f;
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vaddy.x vf7, vf7, vf7y\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "qmfc2.ni $2, vf7\n"
                             "mtc1 $2, %0\n"
                             : "=f"(f) : "r"(v) : "$2", "memory");
        *(float *)(w + 0x48) = f;
        nf = flags & ~mask;
        *(int *)(w + 0x40) = nf;
        if (!(nf & 0x800))
            *(int *)(w + 0x40) = nf | 0x400;
        isysAddGroupWithLinkParam(obj, man->gA0, 0, 0);
        _isysDeleteGroup(obj, man->g9C, 0);
        }
        ret = 1;
    }
end:
    return ret;
}
#endif
