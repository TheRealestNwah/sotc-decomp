extern void *GetCharacterClass(void *);

void SetCharacterObjForceNoExpressionInterp(void *actor)
{
    (*(signed char *)((char *)(GetCharacterClass(actor)) + 0x528)) = 1;
}
