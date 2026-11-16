typedef struct {
    unsigned int ref;
    char pad4[0x18];
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    char pad48[4];
    float x4C;
    int x50;
    int x54;
    int x58;
} SpriteParam;

typedef struct {
    SpriteParam *p;
    int pad4;
    int tex;
    int padC;
    float fade;
    float alpha;
} SpriteMenuParam;

extern int DldSysUndefSymbol;
extern void spriteInitObject(void *, int);
extern void spriteSetFade(void *, float);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetTextureCoordinateUV(void *, float, float, float, float);
extern void spriteSetColor(void *, unsigned char, unsigned char, unsigned char, unsigned char);
extern void spriteSetScale(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteSetPriority(void *, int);
extern void spriteSetBlendMode(void *, int, int, int);

static inline char *resolveRef(unsigned int *ref)
{
    unsigned int r = *ref & 0x3FFFF;
    int *b = r ? *(int **)((char *)ref - r) : 0;

    return (b != 0 && b != (int *)DldSysUndefSymbol) ? (char *)b[4] : 0;
}

void SpriteMenuSetSpriteObjectParam(void *obj, SpriteMenuParam *mp)
{
    int mode = 0;
    SpriteParam *p = mp->p;
    int tex = mp->tex;

    if (tex == 0)
        tex = *(int *)(resolveRef(&p->ref) + 0xC);
    spriteInitObject(obj, tex);
    spriteSetFade(obj, mp->fade);
    spriteSetPosition(obj, p->x1C, p->x20);
    spriteSetTextureCoordinateUV(obj, p->x2C, p->x30, p->x34, p->x38);
    spriteSetColor(obj, (unsigned int)p->x3C, (unsigned int)p->x40, (unsigned int)p->x44,
                   (unsigned int)mp->alpha);
    spriteSetScale(obj, p->x24, p->x28);
    spriteSetRotation(obj, p->x4C);
    spriteSetPriority(obj, 1);
    switch (p->x50) {
    case 0:
        mode = 0;
        break;
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 3;
        break;
    case 4:
        mode = 4;
        break;
    case 5:
        mode = 5;
        break;
    case 6:
        mode = 6;
        break;
    }
    spriteSetBlendMode(obj, mode, p->x54, p->x58);
}