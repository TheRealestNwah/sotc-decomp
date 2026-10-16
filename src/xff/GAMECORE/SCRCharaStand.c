extern void *GetCharacterClass(void *);

void SCRCharaStand(void *actor)
{
    char *cls;

    cls = GetCharacterClass(actor);
    *(int *)(cls + 0x7E4) = 0;
    *(int *)(cls + 0x7EC) = 0;
    *(int *)(cls + 0x81C) = 0;
    *(int *)(cls + 0x818) = 0;
    *(int *)(cls + 0x814) = 0;
}
