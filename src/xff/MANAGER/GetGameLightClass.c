char *GetGameLightClass(unsigned char *p)
{
    if (p[0x8] != 0x1A) {
        return 0;
    }
    return (char *)p + 0x20;
}
