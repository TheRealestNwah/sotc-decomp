char *GetMeshClass(unsigned char *p)
{
    if (p[0x8] != 0x23) {
        return 0;
    }
    return (char *)p + 0x20;
}
