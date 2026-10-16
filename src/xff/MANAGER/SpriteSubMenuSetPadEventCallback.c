void SpriteSubMenuSetPadEventCallback(unsigned char *o, int i, int cb)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    *(int *)(*(char **)(c + 4) + off + 0x40) = cb;
}
