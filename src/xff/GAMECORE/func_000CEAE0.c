/* Parked draft: boss-status map icons. Builds a per-boss "show" flag array on the stack (alloca)
   from the game flags (the active boss is hidden while its boot check passes), then draws every
   sprite of each shown boss's icon group at the boss-relative compass position. Continues in
   func_000CECE0 (epilogue). Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern void SpriteMenuSetSpriteObjectParam(void *, void *);
extern int _gameFlagChk(int);
extern int bossStatBootChk(void);
extern int bossStatGetActiveBoss(void);
extern void spriteDrawSprite(void *, int, int, int, float, float, float, float, float, float);

typedef struct {
    char pad0[4];
    char *groups;
} IconSet;

static void func_000CEAE0(IconSet *icons, char *cam)
{
    int *sh = DldSysUndefSymbol != (int)SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    char *bosses = (char *)sh[4];
    int count = sh[3];
    int active = bossStatGetActiveBoss();
    int booting = 0;
    int show[count];
    int i;
    char *b;

    if (active != 0)
        booting = bossStatBootChk() > 0;
    b = bosses;
    for (i = 0; i < count; i++, b += 0xEC) {
        int v = 0;
        if (booting == 0 || active != (int)b)
            v = _gameFlagChk(*(int *)(b + 0x18)) != 0;
        show[i] = v;
    }
    b = bosses;
    for (i = 0; i < count; i++, b += 0xEC) {
        if (show[i] != 0) {
            char *group = icons->groups + *(int *)(b + 0x14) * 0x44;
            unsigned int n = (*(unsigned int *)(group + 8) >> 4) & 0x3FF;
            unsigned int k;
            char sprite[0x40] __attribute__((aligned(16)));

            for (k = 0; k < n; k++) {
                char *entry = *(char **)(group + 4) + k * 0x1C;
                float s = *(float *)(cam + 0x18);

                SpriteMenuSetSpriteObjectParam(sprite, entry);
                spriteDrawSprite(sprite, *(int *)(group + 0x24), *(int *)(cam + 0x58) - 0x18,
                                 *(int *)(*(char **)entry + 0x70),
                                 *(float *)(cam + 0x50) / s - *(float *)(cam + 0x34),
                                 *(float *)(cam + 0x54) / s - (*(float *)(cam + 0x3C) + *(float *)(cam + 0x38) * -0.067f),
                                 s, s, *(float *)(group + 0x30), *(float *)(cam + 0x14));
            }
        }
    }
}
#endif
