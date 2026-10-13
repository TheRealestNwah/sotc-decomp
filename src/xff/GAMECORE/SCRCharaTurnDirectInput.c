extern void *GetCharacterClass();

void SCRCharaTurnDirectInput(float fparg0)
{
    (*(float *)((char *)(GetCharacterClass()) + 0x7E8)) = fparg0;
}
