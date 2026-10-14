extern int bossStatBootChk();

int GAMEUTIL_is_boss_booting(void)
{
    return bossStatBootChk() > 0;
}
