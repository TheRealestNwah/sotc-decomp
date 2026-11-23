/*
 * Parked: 2 diffs. Global, called from InitSpriteObj (creates one sprite
 * per definition and applies its position, UVs, colour, scale, rotation
 * and blend mode).
 * Remaining: the list->sprites load and the i*4 shift swap registers
 * (Original: v1 = list->sprites, v0 = i << 2). The empty asm statements
 * force the Original's order of the slot address, the `move a0, s1` and
 * the two stores before the 0xC float load.
 */
#ifdef NONMATCHING
extern int sheetFsLanguageCode;
extern int DldSysUndefSymbol;
extern void *spriteCreateObject(void *, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetTextureCoordinateUV(void *, float, float, float, float);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetScale(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteSetPriority(void *, int);
extern void spriteSetBlendMode(void *, int, int, int);

typedef struct {
    void **sprites;
    int count;
    int max;
} SpriteList;

typedef struct {
    unsigned int sym;
    int w4;
    int layer;
    float x, y;
    float sx, sy;
    float u0, v0, u1, v1;
    float r, g, b, a;
    float rot;
    int blend;
    int b1, b2;
    int w4C;
    void *sprite;
} SpriteDef;

static inline int *dldResolve(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

void func_00098A88(void *heap, int unused, SpriteList *list, SpriteDef *d)
{
    int i;
    for (i = 0; i < list->count; i++) {
        int *tbl = dldResolve(&d->sym);
        int tex = dldResolve((unsigned int *)tbl + sheetFsLanguageCode - 1)[3];
        int mode;
        void *sp;
        mode = 0;
        if (list->max < d->layer + 1)
            list->max = d->layer + 1;
        sp = spriteCreateObject(heap, tex);
        {
            void **slot = &list->sprites[i];
            __asm__ __volatile__("" : : "r"(slot));
            {
                register void *a __asm__("$4") = sp;
                __asm__ __volatile__("" : "+r"(a));
                *slot = sp;
                d->sprite = sp;
                __asm__ __volatile__("" : : );
                spriteSetPosition(a, d->x, d->y);
            }
        }
        spriteSetTextureCoordinateUV(sp, d->u0, d->v0, d->u1, d->v1);
        spriteSetColor(sp, (unsigned char)(unsigned int)d->r, (unsigned char)(unsigned int)d->g,
                       (unsigned char)(unsigned int)d->b, (unsigned char)(unsigned int)d->a);
        spriteSetScale(sp, d->sx, d->sy);
        spriteSetRotation(sp, d->rot);
        spriteSetPriority(sp, 1);
        switch (d->blend) {
        case 0: mode = 0; break;
        case 1: mode = 1; break;
        case 2: mode = 2; break;
        case 3: mode = 3; break;
        case 4: mode = 4; break;
        case 5: mode = 5; break;
        case 6: mode = 6; break;
        }
        spriteSetBlendMode(sp, mode, d->b1, d->b2);
        d++;
    }
}
#endif
