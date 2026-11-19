/* Boss demo start: boss status lookup (as in bossStatTimeAttackJumpSekiban), then a VU0 vadd.xyz of the seamless-area centre onto the negated boss offset (one asm run). The 16-byte copy of the offset vector uses a union with a two-long view so gcc emits ld/sd, not ldl/ldr; the y component is pinned to $f1 for the Original register choice. */
extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int D_00179F90;
extern char *D_00179F94;
extern int gameflowBootBossWait;
extern int gstatTimeAttackMode;
extern char gcGlobalVar[];
extern int _gameWorkChk(int);
extern void gameflowSetJumpSekiban(int);
extern int SCRGetFirstObj(void *);
extern void YattsukeGetSeamlessAreaCenter(void *, int);
extern void gameflowSetPos(int, float, float, float, float, float, float);
extern void bossCloudStart(void);
extern void func_0000FA50(void);
extern void gStatStartTimeAttack(void);

typedef struct {
    char pad[0xEC];
} BossStatus;

typedef union {
    struct {
        float x, y, z, w;
    };
    long l[2];
} Vec;

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

void bossStatStartDemo(void)
{
    char *s = getBossStatus();
    Vec center;
    Vec v;
    Vec tmp;
    int obj;

    gameflowBootBossWait = 0;
    if (*(unsigned int *)(s + 0x50) & 1) {
        gameflowSetJumpSekiban(1);
        obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
        if (obj != 0) {
            tmp.x = -*(float *)(s + 0x64);
            {
                register float y __asm__("$f1") = *(float *)(s + 0x68);

                tmp.y = y;
            }
            tmp.z = -*(float *)(s + 0x6C);
            tmp.w = 1.0f;
            v = tmp;
            YattsukeGetSeamlessAreaCenter(&center, *(unsigned char *)(s + 0x51));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%1)\n"
                                 :
                                 : "r"(&center), "r"(&v)
                                 : "memory");
            gameflowSetPos(obj, -v.x, v.y, -v.z, 0.0f, *(float *)(s + 0x70), 0.0f);
        }
    }
    if ((*(unsigned int *)(s + 0x50) >> 2) & 1)
        bossCloudStart();
    func_0000FA50();
    if (gstatTimeAttackMode != 0)
        gStatStartTimeAttack();
}
