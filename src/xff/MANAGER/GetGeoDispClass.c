char *GetGeoDispClass(unsigned char *p)
{
    if (p[8] != 0x24) {
        return 0;
    }
    return (char *)p + 0x20;
}
