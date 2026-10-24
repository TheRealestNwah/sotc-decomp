extern void DecreaseDamageLockTime(void *, float);

void ResetCharacterClassMailRelationalTriggerFlags(char *character, float dt)
{
    DecreaseDamageLockTime(character + 0x200, dt);
}
