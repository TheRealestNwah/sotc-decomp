extern int _gameFlagChk(int);

int bossStatChkDeadBoss(void *arg0)
{
    return _gameFlagChk((*(int *)((char *)(arg0) + 0x18))) == 0;
}
