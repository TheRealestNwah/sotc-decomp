char *GetWindowClass(unsigned char *p)
{
    if (p[0x8] != 0xC) {
        return 0;
    }
    return (char *)p + 0x20;
}
