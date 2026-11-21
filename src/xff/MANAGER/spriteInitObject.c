/* Needs -fno-strict-aliasing (config/ee_cflags.json): the Original keeps every
   sprite store ahead of the texture-size loads that follow it. */
typedef struct {
    unsigned long lower : 40;
    unsigned long mode : 4;
    unsigned long source : 2;
    unsigned long destination : 2;
    unsigned long uvMode : 1;
    unsigned long f49 : 2;
    unsigned long f51 : 2;
    unsigned long upper : 11;
} SpriteFlags;
typedef struct {
    unsigned int pad0 : 16;
    unsigned int tw : 4;
    unsigned int th : 4;
    unsigned int pad24 : 8;
} TexSize;
typedef struct {
    char pad0[0x1C];
    TexSize size;
} TexInfo;
typedef struct {
    char pad0[0x20];
    TexInfo *info;
} Texture;
typedef struct {
    Texture *tex;
    unsigned char r, g, b, a;
    float fade;
    int colorMask;
    int u0, v0;
    int u1, v1;
    float s0, t0;
    float s1, t1;
    float x, y;
    float w, h;
    float scaleX, scaleY;
    union {
        float rotation;
        SpriteFlags flags;
    } u48;
} Sprite;

void spriteInitObject(Sprite *s, Texture *tex)
{
    TexInfo *info = tex->info;
    float zero = 0.0f;
    float one = 1.0f;

    s->tex = tex;
    s->y = zero;
    s->x = zero;
    s->s0 = zero;
    s->t0 = zero;
    s->colorMask = 0xFFFFFF;
    s->s1 = one;
    s->t1 = one;
    s->u0 = 0;
    s->v0 = 0;
    s->u1 = (1 << info->size.tw) - 1;
    s->v1 = (1 << info->size.th) - 1;
    s->u48.rotation = zero;
    s->scaleY = one;
    s->scaleX = one;
    s->a = 0x80;
    s->b = 0x80;
    s->g = 0x80;
    s->r = 0x80;
    s->fade = one;
    s->u48.flags.mode = 1;
    s->u48.flags.source = 0;
    s->u48.flags.destination = 1;
    s->u48.flags.uvMode = 0;
    s->u48.flags.f49 = 1;
    s->u48.flags.f51 = 1;
    s->w = 1 << info->size.tw;
    s->h = 1 << info->size.th;
}
