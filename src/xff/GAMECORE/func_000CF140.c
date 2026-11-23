/* Parked: 2 diffs, same size. Lays out the MAP_ALL scroll-map sprites
 * (scale, scroll clamps, texture ST) and draws them. Remaining: the Original
 * stores +0x34 before +0x38 but allocates W(0x2C) to f5 and the screen
 * height to f6; every statement order that stores +0x34 first swaps f5/f6
 * (10 diffs). The second draw needs the held x temp (drawParts2) to load
 * +0x1C before SpriteMenuGetProgressiveOffset. 0x3F5B6DB6 spells 0.85714281f.
 * Permuter: base scoring failed (inf). */

#ifdef NONMATCHING

extern const char RO_00180BE0[];
extern const char RO_00180BE8[];

typedef struct { float f[18]; unsigned long pad:49; unsigned long a:2; unsigned long b:2; unsigned long rest:11; } Spr;
extern Spr B_0019FC50;
extern Spr B_0019FCA0;

extern int MakeStrHashValue(const char *);
extern char *SpriteMenuGetLayerByHash(void *, int);
extern void *SpriteMenuGetPartsParamByHashStr(void *, const char *, const char *);
extern char *SpriteMenuGetPartsDefByHashStr(void *, const char *, const char *);
extern int SpriteMenuGetProgressiveOffset(char *);
extern void SpriteMenuSetSpriteObjectParam(void *, void *);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void spriteSetTextureCoordinateST(void *, float, float, float, float);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);

#define W(type, o) (*(type *)(w + (o)))
#define L(type, o) (*(type *)(layer + (o)))

static inline void drawParts(void *menu, char *layer, Spr *spr, const char *name)
{
    char *def = SpriteMenuGetPartsDefByHashStr(menu, RO_00180BE0, name);
    spriteDrawSprite(spr, L(int, 0x24), L(float, 0x1C), L(float, 0x20) + SpriteMenuGetProgressiveOffset(layer), L(float, 0x28), L(float, 0x2C), L(float, 0x30), L(float, 0xC), (L(unsigned int, 8) >> 14) & 0xF, *(int *)(def + 0x70));
}

static inline void drawParts2(void *menu, char *layer, Spr *spr, const char *name)
{
    char *def = SpriteMenuGetPartsDefByHashStr(menu, RO_00180BE0, name);
    float x = L(float, 0x1C);
    float y = L(float, 0x20) + SpriteMenuGetProgressiveOffset(layer);
    spriteDrawSprite(spr, L(int, 0x24), x, y, L(float, 0x28), L(float, 0x2C), L(float, 0x30), L(float, 0xC), (L(unsigned int, 8) >> 14) & 0xF, *(int *)(def + 0x70));
}

static inline void drawAll(void *menu)
{
    char *layer = SpriteMenuGetLayerByHash(menu, MakeStrHashValue(RO_00180BE0));
    drawParts(menu, layer, &B_0019FCA0, RO_00180BE8);
    drawParts2(menu, layer, &B_0019FC50, RO_00180BE0);
}

static void func_000CF140(void *menu, int unused, char *w)
{
    char *layer;
    float s, sx, sy;

    layer = SpriteMenuGetLayerByHash(menu, MakeStrHashValue(RO_00180BE0));
    SpriteMenuSetSpriteObjectParam(&B_0019FC50, SpriteMenuGetPartsParamByHashStr(menu, RO_00180BE0, RO_00180BE0));
    SpriteMenuSetSpriteObjectParam(&B_0019FCA0, SpriteMenuGetPartsParamByHashStr(menu, RO_00180BE0, RO_00180BE8));
    W(float, 0x40) = getDrawScreenWidth();
    W(float, 0x44) = getDrawScreenHeight() - 12;
    W(float, 0x14) = L(float, 0xC);
    W(int, 0x58) = 0x19;
    W(float, 0x38) = W(float, 0x2C);
    W(float, 0x34) = W(float, 0x28) * W(float, 0x40) * 0.1f;
    W(float, 0x3C) = -W(float, 0x30) * W(float, 0x44) * 0.1f;
    s = W(float, 0x18);
    W(float, 0x48) = -W(float, 0x34) * s;
    W(float, 0x4C) = -(W(float, 0x3C) + W(float, 0x38) * -0.067f) * s;
    sx = (s - 1.0f) * 250.0f;
    if (sx - W(float, 0x48) + 4.0f < W(float, 0x50))
        W(float, 0x50) = sx - W(float, 0x48) + 4.0f;
    if (W(float, 0x50) < -W(float, 0x48) - sx - 4.0f)
        W(float, 0x50) = -W(float, 0x48) - sx - 4.0f;
    sy = (s - 1.0f) * 216.0f;
    if (sy - W(float, 0x4C) + 4.0f < W(float, 0x54))
        W(float, 0x54) = sy - W(float, 0x4C) + 4.0f;
    if (W(float, 0x54) < -W(float, 0x4C) - sy - 4.0f)
        W(float, 0x54) = -W(float, 0x4C) - sy - 4.0f;
    B_0019FC50.f[16] = s;
    B_0019FC50.f[17] = W(float, 0x18) * 0.85714281f;
    B_0019FC50.f[12] = W(float, 0x48) + W(float, 0x50);
    B_0019FC50.f[13] = W(float, 0x4C) + W(float, 0x54);
    B_0019FCA0.a = 0;
    B_0019FCA0.b = 0;
    spriteSetTextureCoordinateST(&B_0019FCA0, 0.0f, 0.0f, 16.0f, 16.0f);
    B_0019FCA0.f[16] = W(float, 0x18) * 16.0f;
    B_0019FCA0.f[17] = W(float, 0x18) * 16.0f * 0.85714281f;
    B_0019FCA0.f[12] = W(float, 0x48) + W(float, 0x50);
    B_0019FCA0.f[13] = W(float, 0x4C) + W(float, 0x54);
    drawAll(menu);
}

#endif
