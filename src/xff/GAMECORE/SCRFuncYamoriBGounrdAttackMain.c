extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

void SCRFuncYamoriBGounrdAttackMain(void *a)
{
    char *c, *p;
    unsigned long m;
    if (*(int *)(GetLayoutClass(a) + 0x124) == 0)
        return;
    c = GetCharacterClass(a);
    m = *(unsigned long *)(c + 0x690) & 0x1E00000;
    p = *(char **)(c + 0x110C);
    if (m == 0xC00000 || m == 0xA00000)
        *(float *)(p + 0x38) = 0.0f;
    else
        *(float *)(p + 0x38) = 1.0f;
}
