extern int MakeStrHashValue(const char *string);
extern void SpriteMenuSetDispFlagByHash(unsigned char *menu, int name, int disp);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern const char RO_0017DB80[];
extern const char RO_0017DB90[];
extern const char RO_0017DBA8[];
extern const char RO_0017DBC0[];
extern const char RO_0017DBD8[];
extern const char RO_0017DBF0[];
extern const char RO_0017DC00[];
extern const char RO_0017DC18[];
extern const char RO_0017DC28[];
extern const char RO_0017DC48[];
extern const char RO_0017DC60[];
extern const char RO_0017DC70[];
extern const char RO_0017DC88[];
extern const char RO_0017DCA0[];
extern const char RO_0017DCB8[];
extern const char RO_0017DCC8[];
extern int D_0017AD10;

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

static int func_00065E68(unsigned char *menu, MemcardMenuState *st)
{
    int layer;

    if (st->request != 0) {
        st->request = 0;
        if (!((st->mask >> st->shift) & 1)) {
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DB80), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DB90), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBA8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBC0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBD8), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DBF0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC00), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC18), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC28), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC48), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC60), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC70), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DC88), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DCA0), 0);
            SpriteMenuSetDispFlagByHash(menu, MakeStrHashValue(RO_0017DCB8), 0);
            layer = getLayerNo(menu, RO_0017DCC8);
            D_0017AD10 = 0x12;
            if (layer != -1) {
                SpriteMenuSetLayer(menu, layer);
                SpriteMenuSetDispFlag(menu, layer, 1);
            }
            st->timer = 0;
            st->step = 1;
            st->request = 0;
            return 1;
        }
    }
    return 0;
}
