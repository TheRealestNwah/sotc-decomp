int SpriteMenuGetPadEvent(unsigned char *p)
{
    char *c = p[8] != 0x21 ? 0 : (char *)p + 0x90;

    return *(int *)(c + 0x10);
}
