int SpriteMenuGetLayerStatus(unsigned char *o, int i)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    return *(int *)(*(char **)(c + 4) + off + 8) & 0xF;
}
