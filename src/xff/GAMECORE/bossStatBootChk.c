extern char *bossStatGetActiveBoss(void);
extern int gStatGetGObjAdrs(void *);
extern int _gameFlagChk(int);

int bossStatBootChk(void)
{
    char *boss = bossStatGetActiveBoss();

    if (boss != 0 && *(void **)(boss + 0xE8) != 0 &&
        gStatGetGObjAdrs(*(void **)(boss + 0xE8)) != 0)
        return _gameFlagChk(*(int *)(boss + 0x1C)) != 0;
    return -1;
}
