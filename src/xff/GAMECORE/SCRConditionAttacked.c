extern int nico_GetCharacterAttackedFlag(void *actor);

int SCRConditionAttacked(void *actor)
{
    return nico_GetCharacterAttackedFlag(actor);
}
