extern int SpriteMenuGetSelectLayer(unsigned char *);
extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(unsigned char *, int);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void SpriteMenuSetLayer(unsigned char *, int);
extern char RO_0017E098[], RO_0017E0B8[], RO_0017E118[], RO_0017E130[], RO_0017E0C8[], RO_0017E148[];
extern void func_00072928(unsigned char *, int, int, int);
extern void func_00072CD0(unsigned char *, int, int);
extern void func_00072EE8(unsigned char *, int, int, int);
extern void func_00073180(unsigned char *, int, int, int);
extern void func_000733D8(unsigned char *, int, int);
extern void func_00073908(unsigned char *, int);

static void T_00073A30(unsigned char *menu, int a1, int a2, int a3)
{
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098))) {
        func_00072928(menu, a1, a2, a3);
        return;
    }
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0B8))) {
        func_00072CD0(menu, a1, a2);
        return;
    }
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118))) {
        func_00072EE8(menu, a1, a2, a3);
        return;
    }
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130))) {
        func_00073180(menu, a1, a2, a3);
        return;
    }
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0C8))) {
        func_000733D8(menu, a2, a3);
        return;
    }
    if (SpriteMenuGetSelectLayer(menu) == SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E148))) {
        if (!(a2 & 3)) return;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E148)), 0);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0C8)), 1);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0C8)));
        func_00073908(menu, a3);
        return;
    }
}
