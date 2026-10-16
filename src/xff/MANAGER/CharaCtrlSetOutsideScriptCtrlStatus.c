extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern unsigned char *GetGeometryPointerObject(void *);

void CharaCtrlSetOutsideScriptCtrlStatus(void *o, int bit)
{
    char *c;
    char *s;
    char *l;
    unsigned char *g;
    long *p;

    c = GetCharacterClass(o);
    if (c == 0) {
        s = 0;
        l = GetLayoutClass(o);
        if (*(int *)(l + 0x124) != 0) {
            g = GetGeometryPointerObject(l + 0xC0);
            if (g[8] == 0x16)
                s = GetCharacterClass(g);
        }
        c = s;
        if (c != 0)
            goto set;
    } else {
set:
        p = (long *)(c + 0x928);
        *p |= (long)1 << bit;
    }
}
