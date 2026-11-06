extern int SeList_decide, SeList_cancel;
extern int B_0018B6A8[];
extern void (*D_0017ADA8[])(int);
extern char RO_0017E0B8[], RO_0017E098[];
extern int sePlaySystemSound(int);
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void iosGsChangeScreenOffset(void);

static void func_00072CD0(void *menu, int *p, unsigned flags)
{
    if (flags & 1) {
        sePlaySystemSound(SeList_decide);
        B_0018B6A8[1] += p[1];
        B_0018B6A8[2] += p[2];
        p[2] = 0;
        p[1] = 0;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0B8)), 0);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)), 1);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
        D_0017ADA8[1](B_0018B6A8[1]);
        D_0017ADA8[2](B_0018B6A8[2]);
        iosGsChangeScreenOffset();
        return;
    }
    if (flags & 2) {
        sePlaySystemSound(SeList_cancel);
        B_0018B6A8[1] += p[1];
        B_0018B6A8[2] += p[2];
        p[2] = 0;
        p[1] = 0;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0B8)), 0);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)), 1);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
        D_0017ADA8[1](B_0018B6A8[1]);
        D_0017ADA8[2](B_0018B6A8[2]);
        iosGsChangeScreenOffset();
        return;
    }
}
