extern int nico_GetCharacterAttackedFlag();

int SCRConditionAttacked(int a, int b, int c, int d)
{
    return nico_GetCharacterAttackedFlag(a, b, c, d);
}
