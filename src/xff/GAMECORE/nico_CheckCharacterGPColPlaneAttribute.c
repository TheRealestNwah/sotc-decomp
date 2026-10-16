extern char *GetCharacterClass(void *);

int nico_CheckCharacterGPColPlaneAttribute(void *a, long mask, long val)
{
    char *c = GetCharacterClass(a);

    int ret = 0;

    if (*(int *)(c + 0x124) != 0) {
        ret = 1;
        if (((*(long *)(c + 0x690) & mask)) != val)
            ret = 0;
    }
    return ret;
}
