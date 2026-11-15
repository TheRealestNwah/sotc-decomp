/* Parked: 86 diffs with -fno-strict-aliasing, same size (135 words). Boss check-point save: boss status lookup (as in bossStatStartDemo), two position records built from the status floats (negated x/z, 12-byte struct copies via ldl/ldr from a Vec3 struct, 16-byte ld/sd copies via a union with a long pair), VU0 vadd.xyz of the seamless-area centre onto two of them, then the hook call with the status byte at +0x52 as the fifth argument. Frame: one local struct (center +0, a +0x10, b +0x20, c +0x30, d +0x40, e +0x50). Remaining: the Original sets up a0/a1/a2/a3 for the shared memset/save call before the boss-status branches (gcc hoists them into the load delay), and sw zero stores are interleaved earlier. */
#ifdef NONMATCHING
extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int D_00179F90;
extern char *D_00179F94;
extern int _gameWorkChk(int);
extern void *memset(void *, int, unsigned int);
extern void gStatCheckPointSave(void *, int, int);
extern void YattsukeGetSeamlessAreaCenter(void *, int);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern void gStatChekcPointSaveHookPlayerHorsePos(void *, void *, void *, void *, int);

typedef struct {
    char pad[0xEC];
} BossStatus;

typedef union {
    struct {
        float x, y, z, w;
    };
    long l[2];
} Vec;

typedef struct {
    float a, b, c;
} Vec3;

static inline char *getBossStatus(void)
{
    int w = _gameWorkChk(8);

    if (w == D_00179F90)
        return D_00179F94;
    D_00179F90 = w;
    if (w == -1) {
        D_00179F94 = 0;
        return 0;
    }
    {
        int *sh = DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;

        D_00179F94 = (char *)((BossStatus *)sh[4] + w);
    }
    return D_00179F94;
}

void func_0000FA50(void)
{
    struct {
        Vec center;
        Vec a;
        Vec b;
        Vec3 c;
        Vec d;
        Vec e;
    } L __attribute__((aligned(16)));
    char *s = getBossStatus();

    if (s == 0) {
        gStatCheckPointSave(&L.b, 0, 0x10);
        return;
    }
    memset(&L.b, 0, 0x10);
    L.b.x = -*(float *)(s + 0x54);
    L.b.y = *(float *)(s + 0x58);
    L.a.l[0] = L.b.l[0];
    *(int *)&L.c.a = 0;
    L.b.z = -*(float *)(s + 0x5C);
    L.a.l[1] = L.b.l[1];
    *(int *)&L.c.c = 0;
    L.c.b = *(float *)(s + 0x60);
    *(Vec3 *)&L.b = L.c;
    memset(&L.e, 0, 0x10);
    L.e.x = -*(float *)(s + 0x64);
    L.e.y = *(float *)(s + 0x68);
    L.d.l[0] = L.e.l[0];
    L.e.x = 0.0f;
    L.e.z = -*(float *)(s + 0x6C);
    L.d.l[1] = L.e.l[1];
    L.e.z = 0.0f;
    L.e.y = *(float *)(s + 0x70);
    L.c = *(Vec3 *)&L.e;
    YattsukeGetSeamlessAreaCenter(&L.center, *(unsigned char *)(s + 0x51));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         :
                         : "r"(&L.center), "r"(&L.a)
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         :
                         : "r"(&L.center), "r"(&L.d)
                         : "memory");
    _gameFlagSet(0x1D);
    gStatChekcPointSaveHookPlayerHorsePos(&L.a, &L.b, &L.d, &L.c, *(unsigned char *)(s + 0x52));
    _gameFlagCls(0x1D);
}
#endif
