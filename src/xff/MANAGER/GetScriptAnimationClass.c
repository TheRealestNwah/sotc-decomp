char *GetScriptAnimationClass(unsigned char *p)
{
    if (p[0x8] != 0xD) {
        return 0;
    }
    return (char *)p + 0x20;
}
