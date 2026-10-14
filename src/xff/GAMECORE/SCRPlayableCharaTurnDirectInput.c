extern void *GetCharacterClass(void *);

void SCRPlayableCharaTurnDirectInput(void *actor, float fparg0)
{
    void *temp_v0;

    temp_v0 = GetCharacterClass(actor);
    (*(float *)((char *)(temp_v0) + 0x768)) = fparg0;
    (*(long *)((char *)(temp_v0) + 0x7D8)) = (long) ((*(long *)((char *)(temp_v0) + 0x7D8)) | 0x40000);
}
