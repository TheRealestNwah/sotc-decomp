extern void *GetDamageClass(void *);

int nico_GetCharacterAttackedFlag(void *actor)
{
    return *(int *)GetDamageClass(actor) == 3;
}
