extern char RO_0017E0C8[];
extern char *D_STR_0017AE58[];
extern int MakeStrHashValue(const char *);
extern char *SpriteMenuGetLayerByHash(void *, int);
extern int SpriteMenuGetPartsDefValueByHashStr(void *, char *, char *);
extern void SpriteMenuSetPartsDefValueByHashStr(void *, char *, char *, int);

static void func_00073908(void *menu, int val)
{
    int *f;
    char **p;
    int cur;
    unsigned i = 0;
    int v;
    f = (int *)(SpriteMenuGetLayerByHash(menu, MakeStrHashValue(RO_0017E0C8)) + 0x34);
    v = SpriteMenuGetPartsDefValueByHashStr(menu, RO_0017E0C8, D_STR_0017AE58[(f[1] << 11) >> 22]);
    p = D_STR_0017AE58;
    cur = v;
    while (i < 10) {
        i++;
        if (SpriteMenuGetPartsDefValueByHashStr(menu, RO_0017E0C8, *p) == val) {
            SpriteMenuSetPartsDefValueByHashStr(menu, RO_0017E0C8, *p, cur);
            break;
        }
        p++;
    }
    SpriteMenuSetPartsDefValueByHashStr(menu, RO_0017E0C8, D_STR_0017AE58[(f[1] << 11) >> 22], val);
}
