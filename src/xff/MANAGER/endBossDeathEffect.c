extern int D_00130380;
extern int D_00130388;

void endBossDeathEffect(void)
{
    D_00130388 = 0;
    D_00130380 &= ~1;
}
