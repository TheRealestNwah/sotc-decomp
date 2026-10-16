int FlushSpriteObj(char *obj)
{
    char *sprite = ((unsigned char *)obj)[8] == 0xE ? obj + 0x90 : 0;

    *(int *)(sprite + 0x4C) = 0;
    if (*(int *)(sprite + 0x50) == 0) {
        *(int *)(sprite + 0x50) = 1;
    }
    return 0;
}
