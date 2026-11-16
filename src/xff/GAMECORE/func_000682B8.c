extern int MakeStrHashValue(const char *string);
extern void SpriteMenuSetDispFlagByHash(unsigned char *menu, int name, int disp);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern const char RO_0017DB80[];
extern const char RO_0017DBA8[];
extern const char RO_0017DBC0[];
extern const char RO_0017DBD8[];
extern const char RO_0017DBF0[];
extern const char RO_0017DC00[];
extern const char RO_0017DCB8[];
extern const char RO_0017DCC8[];
extern const char RO_0017DD90[];
extern const char RO_0017DDA0[];
extern const char RO_0017DDB8[];
extern const char RO_0017DDC8[];
extern const char RO_0017DDE0[];
extern int D_0017AD18;

typedef struct {
    int pad0;
    int step;
    char pad8[8];
    int request;
    int mask;
    char pad18[4];
    int timer;
    char pad20[4];
    int shift;
} MemcardMenuState;

static inline int getLayerNo(unsigned char *menu, const char *name)
{
    return name ? SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(name)) : -1;
}

static int func_000682B8(unsigned char *menu, MemcardMenuState *st)
{
    int layer;
    int bit;

    if (st->request != 0) {
        bit = st->shift == -1 ? 3 : 1 << st->shift;
        st->request = 0;
        if (!(st->mask & bit)) {
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DB80), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBA8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DDA0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DD90), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DDB8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DDC8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DDE0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBC0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBD8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBF0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC00), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DCB8), 0);
            st->step = 2;
            st->timer = 0;
            st->request = 0;
            layer = getLayerNo(menu, RO_0017DCC8);
            D_0017AD18 = 0xF;
            if (layer != -1) {
                SpriteMenuSetLayer(menu, layer);
                SpriteMenuSetDispFlag(menu, layer, 1);
            }
            return 1;
        }
    }
    return 0;
}
