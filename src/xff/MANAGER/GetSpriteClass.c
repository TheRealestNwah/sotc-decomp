char *GetSpriteClass(unsigned char *p)
{
    if (p[0x8] != 0xE) {
        return 0;
    }
    return (char *)p + 0x90;
}
