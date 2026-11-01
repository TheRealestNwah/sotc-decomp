extern int *DldSysUndefSymbol;
extern char *bossStatGetActiveBoss(void);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int GAMEUTIL_is_boss_battle_area(void *pos)
{
    char buf[0x60];
    char *boss = bossStatGetActiveBoss();
    char *cls;
    void *vol;

    if (boss != 0 && (cls = dldBase((unsigned int *)(boss + 0xE0))) != 0 && (vol = *(void **)(cls + 8)) != 0
        && dldElem((unsigned int *)(boss + 0xE4)) != 0)
        return CheckPositionInsideOfJudgeVolumeObject(buf, vol, boss + 0xE4, pos);
    return 0;
}
