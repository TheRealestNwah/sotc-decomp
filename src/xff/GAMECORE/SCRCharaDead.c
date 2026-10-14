extern void *GetCharacterClass(void *);

void SCRCharaDead(void *actor)
{
    void *temp_v0;

    temp_v0 = GetCharacterClass(actor);
    (*(long *)((char *)(temp_v0) + 0x858)) = (long) ((*(long *)((char *)(temp_v0) + 0x858)) | 0x200);
}
