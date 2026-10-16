void SpriteMenuSetCheckBoxByPartsId(unsigned char *o, int id, int idx, unsigned int val)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + id * 0x44;

    if (idx > 0 && idx < (int)((*(unsigned int *)(e + 8) >> 4) & 0x3FF)) {
        char *p = *(char **)(*(char **)(e + 4) + idx * 28);

        if (val < 2)
            *(int *)(p + 0xC) = val;
    }
}
