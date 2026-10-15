extern int DldSysUndefSymbol;

char *get_type_parameter_segment_motion_ik_base(char **a)
{
    unsigned int *h = *(unsigned int **)(*a + 0x18);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return p + 0xC;
}
