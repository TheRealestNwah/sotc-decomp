extern char *GetCharacterClass();

void ChangeCharacterObjControlTarget(int a, int b)
{
    *(int *)(GetCharacterClass(a) + 0x950) = b;
}
