char *getEventScriptClass(unsigned char *p)
{
    if (p[0x8] != 0x20) {
        return 0;
    }
    return (char *)p + 0x20;
}
