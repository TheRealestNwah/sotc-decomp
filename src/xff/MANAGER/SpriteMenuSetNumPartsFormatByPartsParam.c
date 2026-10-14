void SpriteMenuSetNumPartsFormatByPartsParam(int a, char *p, unsigned char f)
{
    *(int *)(p + 0x18) = (*(int *)(p + 0x18) & 0xF00FFFFF) | (f << 20);
}
