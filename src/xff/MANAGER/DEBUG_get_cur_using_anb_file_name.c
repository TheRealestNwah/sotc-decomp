extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern char *GetCharacterClass(void *);
extern char *DEBUG_get_base_name(char *);

static inline int *dldObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}

char *DEBUG_get_cur_using_anb_file_name(void *chr, char *dflt)
{
    if (chr != 0) {
        char *cls = GetCharacterClass(chr);
        if (cls != 0) {
            char **pp = (char **)(cls + 0x1C0);
            if (pp == 0) return 0;
            if (*pp == 0) return 0;
            if ((int *)dldObj((unsigned int *)(*pp + 0x50))[2] == &_AnimObjDef)
                return DEBUG_get_base_name(*(char **)dldElem((unsigned int *)(*pp + 0x50)));
            return dflt;
        }
    }
    return 0;
}
