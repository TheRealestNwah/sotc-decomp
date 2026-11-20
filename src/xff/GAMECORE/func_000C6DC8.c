extern char *g_strReplayPauseLayerDef[];
extern char RO_00180918[];
extern char RO_00180928[];
extern char RO_00180980[];
extern char RO_00180990[];
extern char RO_001809A0[];
extern char RO_001809B8[];
extern char RO_001809D0[];
extern char RO_001807B8[];
extern int B_0019CF40;
extern char rootPtn[];
extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(int, int);
extern void SpriteMenuSetDispFlag(int, int, int);
extern void SpriteMenuSetLayer(int, int);
extern int SpriteMenuGetMenuIdByHash(int, int, int);
extern void SpriteMenuSetSelectMenuId(int, int);
extern void SelectOmakeItem(int, int);
extern void st_pausemenu_load_omake_chara(int *);
extern void *gcCreateScriptObj(void *, int *, void *, int, int, int, const char *);

typedef struct {
    char pad0[4];
    int state;
    char pad8[4];
    unsigned int flags;
    char pad10[8];
    int f18;
    int layerIndex;
} PauseCtx;

static void func_000C6DC8(int menu, PauseCtx *ctx, int event, int id)
{
    char *name;

    switch (ctx->state) {
    case 0xE:
        if (event & 1) {
            SelectOmakeItem(menu, id);
            return;
        }
        if (event & 2) {
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180918)), 0);
            SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180928)));
            SpriteMenuSetSelectMenuId(menu, SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180928), MakeStrHashValue(RO_00180980)));
            ctx->state = 0xF;
            B_0019CF40 = 0;
            gcCreateScriptObj(st_pausemenu_load_omake_chara, &B_0019CF40, rootPtn, 0x1000, 0, 8, RO_00180990);
            return;
        }
        break;
    case 0x10:
        break;
    default:
    if (event & 1) {
        name = g_strReplayPauseLayerDef[ctx->layerIndex];
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(name), MakeStrHashValue(RO_001809A0)))
            ctx->state = 9;
        else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(name), MakeStrHashValue(RO_001809B8)))
            ctx->state = 3;
        else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(name), MakeStrHashValue(RO_001809D0)))
            ctx->state = 4;
        else if (ctx->layerIndex != 0 && id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(name), MakeStrHashValue(RO_00180980)))
            ctx->state = 0xE;
        else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(name), MakeStrHashValue(RO_001807B8)))
            ctx->state = 0x10;
    } else if (event & 2) {
        ctx->state = 9;
    }
    }
}
