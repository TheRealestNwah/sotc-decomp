/* 1.1666667f spells 0x3F955555 under gcc 2.96. */
extern int MakeStrHashValue(char *);
extern char *SpriteMenuGetLayerByHash(int, int);
extern char *SpriteMenuGetPartsDefByHashStr(int, char *, char *);
extern int SpriteMenuGetProgressiveOffset(char *);
extern void SpriteMenuSetSpriteObjectParam(void *, void *);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);
/* spriteDrawSprite with its first float moved before the int argument: EABI passes it in $f12 either way, and this
   argument order loads layer +0x1C ahead of +0x24 like the Original. */
#define spriteDrawSpriteXFirst ((void (*)(void *, float, int, float, float, float, float, float, int, int))spriteDrawSprite)
extern void spriteSetPosition(void *, float, float);
extern char B_0019FC50[];
extern char B_0019FCA0[];
extern float D_0017B398;
extern float D_0017B39C;
extern float D_0017B3A8;
extern char *D_STR_0017B3B0[];
extern char RO_00180BE0[];
extern char RO_00180BE8[];

#define F(p, o) (*(float *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define U(p, o) (*(unsigned int *)((p) + (o)))

static void func_000D05F8(int menu)
{
    char *layer;
    char *def;
    char *obj;
    char **item;
    unsigned int i;
    int j;
    int k;
    char spr[0x50];

    layer = SpriteMenuGetLayerByHash(menu, MakeStrHashValue(RO_00180BE0));
    def = SpriteMenuGetPartsDefByHashStr(menu, RO_00180BE0, RO_00180BE8);
    spriteDrawSprite(B_0019FCA0, I(layer, 0x24), F(layer, 0x1C), F(layer, 0x20) + (float)SpriteMenuGetProgressiveOffset(layer), F(layer, 0x28), F(layer, 0x2C), F(layer, 0x30), F(layer, 0xC), (U(layer, 0x8) >> 14) & 0xF, I(def, 0x70));
    def = SpriteMenuGetPartsDefByHashStr(menu, RO_00180BE0, RO_00180BE0);
    spriteDrawSpriteXFirst(B_0019FC50, F(layer, 0x1C), I(layer, 0x24), F(layer, 0x20) + (float)SpriteMenuGetProgressiveOffset(layer), F(layer, 0x28), F(layer, 0x2C), F(layer, 0x30), F(layer, 0xC), (U(layer, 0x8) >> 14) & 0xF, I(def, 0x70));
    item = D_STR_0017B3B0;
    for (i = 0; i < 16; i++) {
        layer = SpriteMenuGetLayerByHash(menu, MakeStrHashValue(*item));
        F(layer, 0x1C) = D_0017B398;
        F(layer, 0x20) = D_0017B39C + 32.0f / D_0017B3A8;
        F(layer, 0x28) = D_0017B3A8;
        F(layer, 0x2C) = D_0017B3A8;
        for (j = 0; j < (int)((U(layer, 0x8) >> 4) & 0x3FF); j++) {
            void **p = (void **)(*(char **)(layer + 4) + j * 0x1C);
            obj = *p;
            SpriteMenuSetSpriteObjectParam(spr, p);
            spriteSetPosition(spr, F(obj, 0x1C), F(obj, 0x20) * 1.1666667f);
            spriteDrawSpriteXFirst(spr, F(layer, 0x1C), I(layer, 0x24), F(layer, 0x20) + (float)SpriteMenuGetProgressiveOffset(layer), F(layer, 0x28), F(layer, 0x2C), F(layer, 0x30), F(layer, 0xC), (U(layer, 0x8) >> 14) & 0xF, I(obj, 0x70));
        }
        item++;
    }
}
