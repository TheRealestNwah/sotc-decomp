extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern unsigned char *GetGeometryPointerObject(void *);

void CharaCtrlSetScriptCtrlStatusCallBack(void *o, int a, int b, int c2, int d, int e, int f, int g2)
{
    char *c;
    char *s;
    char *l;
    unsigned char *g;
    int *p;

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
        p = (int *)(c + 0x930);
        p[0] = a;
        p[1] = b;
        p[2] = c2;
        p[3] = d;
        p[4] = e;
        p[5] = f;
        p[6] = g2;
    }
}
