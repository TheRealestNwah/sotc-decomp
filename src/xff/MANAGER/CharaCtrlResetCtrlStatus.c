typedef struct {
    long v[62];
} CtrlBlk;

extern CtrlBlk D_001368C0;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern unsigned char *GetGeometryPointerObject(void *);

void CharaCtrlResetCtrlStatus(void *o)
{
    char *c;
    char *s;
    char *l;
    unsigned char *g;

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
        *(CtrlBlk *)(c + 0x760) = D_001368C0;
    }
}
