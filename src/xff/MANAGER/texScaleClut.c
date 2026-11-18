#ifdef NONMATCHING /* 7 diffs: addu operand order (a0 = a1 + t3) and the following a0/v1 swap in the first clamp block */
typedef struct Rgba {
    unsigned char r, g, b, a;
} Rgba;

typedef struct TexWork {
    char pad0[0x40];
    Rgba *clut;
} TexWork;

typedef struct Texture {
    char pad0[0xC];
    TexWork *work;
    char pad10[0x8];
    int clutOffset;
    int format;
} Texture;

typedef struct TexObject {
    char pad0[0x20];
    Texture *texture;
} TexObject;

typedef struct IColor {
    int r, g, b, a;
} IColor __attribute__((aligned(8)));

static inline IColor scaleColor(Rgba *c, float *s)
{
    IColor r;

    r.r = c->r * s[0];
    r.g = c->g * s[1];
    r.b = c->b * s[2];
    r.a = c->a * s[3];
    return r;
}

#define CLAMP(x) ((x) < 0x100 ? ((x) < 0 ? 0 : (x)) : 0xFF)

void texScaleClut(TexObject *object, float *scale)
{
    Texture *texture = object->texture;
    int count = 0;
    Rgba *dest = texture->work->clut;
    Rgba *src = (Rgba *)((char *)texture + texture->clutOffset);
    int i;

    switch (texture->format & 0x3F) {
    case 0x13:
    case 0x1B:
        count = 0x100;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        count = 0x10;
        break;
    }
    if (count) {
        for (i = 0; i < count; i++) {
            Rgba *sp = &src[i];
            IColor c = scaleColor(sp, scale);
            dest[i].r = CLAMP(c.r);
            dest[i].g = CLAMP(c.g);
            dest[i].b = CLAMP(c.b);
            dest[i].a = CLAMP(c.a);
        }
    }
}
#endif
