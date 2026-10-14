extern void _gameFlagCls(int);
extern void *D_00179F98;

void bossStatSetDeadBoss(void *arg0)
{
    D_00179F98 = arg0;
    _gameFlagCls((*(int *)((char *)(arg0) + 0x18)));
}
