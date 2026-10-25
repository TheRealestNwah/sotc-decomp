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

void texScaleClutAlpha(TexObject *object, float scale)
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
            int alpha = src[i].a * scale;
            dest[i].a = alpha >= 0x100 ? 0xFF : (alpha < 0 ? 0 : alpha);
        }
    }
}
