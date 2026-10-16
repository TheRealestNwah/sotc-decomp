typedef struct {
    long v[16];
} CtrlBlk;

extern CtrlBlk D_00136780;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern unsigned char *GetGeometryPointerObject(void *);

void CharaCtrlResetPlayableCtrlStatus(void *o)
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
        *(CtrlBlk *)(c + 0x7E0) = D_00136780;
    }
}
