extern int DecreaseDamageLockTime();

int ResetCharacterClassMailRelationalTriggerFlags(int a, int b, int c, int d)
{
    return DecreaseDamageLockTime(a + 512, b, c, d);
}
