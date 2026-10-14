extern void *GetCharacterClass(void *);

void SCRCharaTurnDirectInput(void *actor, float fparg0)
{
    (*(float *)((char *)(GetCharacterClass(actor)) + 0x7E8)) = fparg0;
}
