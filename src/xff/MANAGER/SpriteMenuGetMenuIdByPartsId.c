int SpriteMenuGetMenuIdByPartsId(unsigned char *o, int menu, int part)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + menu * 0x44;
    int id;
    if (part > 0 && part < (int)((*(unsigned int *)(e + 8) >> 4) & 0x3FF)) {
        id = *(int *)(*(char **)(*(char **)(e + 4) + part * 0x1C) + 0x14);
        if (id != -1)
            return id;
    }
    return -1;
}
