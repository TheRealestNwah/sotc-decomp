extern char *GetLayoutClass(void *);
extern int *GetDamageClass(void *);
extern void SendDirectDamageLetter(void *, void *, void *, float, void *);
extern void *GetGeometryPointerObject(void *);

int SendCharaAttackMsg(void *from, unsigned char *to, void *a2, void *a3, float damage)
{
    char *lc;
    unsigned char *parent;

retry:
    lc = GetLayoutClass(to);
    if (GetDamageClass(to))
        SendDirectDamageLetter(from, to, a2, damage, a3);
    if (lc && *(int *)(lc + 0x124)) {
        parent = GetGeometryPointerObject(lc + 0xC0);
        if (parent) {
            switch (to[8]) {
            case 0xA:
            case 0xB:
            case 0xD:
            case 0x16:
                to = parent;
                goto retry;
            }
        }
    }
    return 0;
}
