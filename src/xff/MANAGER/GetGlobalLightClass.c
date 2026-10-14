char *GetGlobalLightClass(unsigned char *p)
{
    if (p[0x8] != 0x19) {
        return 0;
    }
    return (char *)p + 0x20;
}
