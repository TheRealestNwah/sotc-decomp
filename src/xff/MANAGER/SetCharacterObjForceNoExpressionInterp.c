extern void *GetCharacterClass();

void SetCharacterObjForceNoExpressionInterp(void)
{
    (*(signed char *)((char *)(GetCharacterClass()) + 0x528)) = 1;
}
