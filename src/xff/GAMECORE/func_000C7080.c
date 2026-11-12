/* Replay/pause menu state machine step. Switch on the state at ctx+4 (3..16, jump
   table RO_00180A20, written out case by case; states 5-8, 10-12 and out of range fall to the common
   tail). State 9 is forced when the pad menu button (0x800) is pressed outside state 14. The common tail
   hides the pause layer and returns 1 when ctx+0xC has bit 4, else returns 0. Continues in func_000C72A8
   (the tail's SpriteMenuSetDispFlag call and epilogue). */
extern char *g_strReplayPauseLayerDef[];
extern char RO_00180918[];
extern int B_0019CF40;
extern struct { char pad[8]; unsigned int buttons; } padManagerData;
extern int SpriteMenuIsFadeCheckAllLayer(int);
extern void SpriteMenuSetDispFlagAll(int, int);
extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(int, int);
extern void SpriteMenuSetDispFlag(int, int, int);
extern void SpriteMenuSetLayer(int, int);
extern void func_000C8B68(void);
extern void func_000C8BE0(void);
extern void SetItemMenuDisp(int);
extern char *GetSpriteMenuClass(int);
extern void OptionMenuStart(int *, int);
extern void scrRun(void);

typedef struct {
    char pad0[4];
    int state;
    char pad8[4];
    unsigned int flags;
    char pad10[8];
    int f18;
    int layerIndex;
} PauseCtx;

static int func_000C7080(int menu, PauseCtx *ctx)
{
    char *layerName = g_strReplayPauseLayerDef[ctx->layerIndex];

    if (SpriteMenuIsFadeCheckAllLayer(menu) != 0)
        return 0;
    if (ctx->state != 0xE && (padManagerData.buttons & 0x800))
        ctx->state = 9;
    switch (ctx->state) {
    case 13:
        if (SpriteMenuIsFadeCheckAllLayer(menu) == 0) {
            SpriteMenuSetDispFlagAll(menu, 0);
            return 1;
        }
        break;
    case 9:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(layerName)), 0);
        return 1;
    case 3:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(layerName)), 0);
        func_000C8B68();
        return 1;
    case 4:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(layerName)), 0);
        ctx->f18 = 0;
        func_000C8BE0();
        return 1;
    case 14:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180918)), 1);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180918)));
        SetItemMenuDisp(menu);
        break;
    case 15:
        if (B_0019CF40 != 0)
            ctx->state = 2;
        break;
    case 16: {
        int done = 0;
        char *cls = GetSpriteMenuClass(menu);

        OptionMenuStart(&done, 0);
        while (done == 0) {
            (*(void (**)(int))(cls + 0x2C))(menu);
            scrRun();
        }
        ctx->state = 2;
        break;
    }
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
    case 11:
    case 12:
    default:
        break;
    }
    if (ctx->flags & 4) {
        ctx->flags = ctx->flags & ~4U;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(layerName)), 0);
        return 1;
    }
    return 0;
}
