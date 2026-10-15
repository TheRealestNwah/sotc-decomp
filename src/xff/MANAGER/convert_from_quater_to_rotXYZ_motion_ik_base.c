extern int DldSysUndefSymbol;
extern void convert_from_quater_to_rotXYZ_direct_motion_ik_base(void *, void *, int);

void convert_from_quater_to_rotXYZ_motion_ik_base(void *a, void *b, char **c)
{
    unsigned int *h = *(unsigned int **)(*c + 0x18);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    convert_from_quater_to_rotXYZ_direct_motion_ik_base(a, b, *(int *)(p + 0x14));
}
