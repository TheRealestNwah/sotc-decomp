char *GetLightClass(unsigned char *p)
{
    if (p[0x8] != 0x13) {
        return 0;
    }
    return (char *)p + 0x20;
}
