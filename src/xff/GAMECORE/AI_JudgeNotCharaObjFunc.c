extern void *GetCharacterClass(void *);

int AI_JudgeNotCharaObjFunc(void *actor)
{
    return GetCharacterClass(actor) == 0;
}
