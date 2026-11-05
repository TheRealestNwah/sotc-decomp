extern const char RO_00180BE0[];
extern const char RO_00180BE8[];

extern char B_0019FC50[];
typedef struct { float f[18]; unsigned long pad:49; unsigned long a:2; unsigned long b:2; unsigned long rest:11; } Spr;
extern Spr B_0019FCA0;
extern float D_0017B398;
extern float D_0017B39C;
extern float D_0017B3A8;

extern int MakeStrHashValue(const char *);
extern char *SpriteMenuGetLayerByHash(void *, int);
extern void *SpriteMenuGetPartsParamByHashStr(void *, const char *, const char *);
extern void SpriteMenuSetSpriteObjectParam(void *, void *);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetTextureCoordinateST(void *, float, float, float, float);

static void func_000D0490(void *menu)
{
    char *layer;

    layer = SpriteMenuGetLayerByHash(menu, MakeStrHashValue(RO_00180BE0));
    SpriteMenuSetSpriteObjectParam(B_0019FC50, SpriteMenuGetPartsParamByHashStr(menu, RO_00180BE0, RO_00180BE0));
    SpriteMenuSetSpriteObjectParam(&B_0019FCA0, SpriteMenuGetPartsParamByHashStr(menu, RO_00180BE0, RO_00180BE8));
    spriteSetPosition(B_0019FC50, D_0017B398, D_0017B39C);
    spriteSetPosition(&B_0019FCA0, 0.0f, 0.0f);
    *(float *)(layer + 0x1C) = 0.0f;
    *(float *)(layer + 0x20) = 32.0f / D_0017B3A8;
    *(float *)(layer + 0x28) = D_0017B3A8;
    *(float *)(layer + 0x2C) = D_0017B3A8;
    B_0019FCA0.a = 0;
    B_0019FCA0.b = 0;
    spriteSetTextureCoordinateST(&B_0019FCA0, 0.0f, 0.0f, 16.0f, 16.0f);
}
