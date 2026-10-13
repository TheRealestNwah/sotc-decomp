extern void *GetCharacterClass();

void SCRCharaDead(void)
{
    void *temp_v0;

    temp_v0 = GetCharacterClass();
    (*(long *)((char *)(temp_v0) + 0x858)) = (long) ((*(long *)((char *)(temp_v0) + 0x858)) | 0x200);
}
