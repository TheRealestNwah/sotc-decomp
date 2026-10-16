extern char *GetCharacterClass(void *);

int nico_CheckCharacterVColPlaneAttribute(void *a, long mask, long val)
{
    char *c = GetCharacterClass(a);

    int ret = 0;

    if (*(int *)(c + 0xF3C) != 0) {
        ret = 1;
        if (((*(long *)(c + 0xF40) & mask)) != val)
            ret = 0;
    }
    return ret;
}
