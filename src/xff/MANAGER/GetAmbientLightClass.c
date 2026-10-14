char *GetAmbientLightClass(unsigned char *p)
{
    if (p[0x8] != 0x14) {
        return 0;
    }
    return (char *)p + 0x1C;
}
