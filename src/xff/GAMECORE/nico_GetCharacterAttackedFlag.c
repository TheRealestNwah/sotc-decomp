extern int *GetDamageClass();

int nico_GetCharacterAttackedFlag(void)
{
    return *GetDamageClass() == 3;
}
