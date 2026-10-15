extern int DldSysUndefSymbol;

int create_particle_texture(int *p)
{
    int *h = p + 1;
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    t = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    return t[3];
}
