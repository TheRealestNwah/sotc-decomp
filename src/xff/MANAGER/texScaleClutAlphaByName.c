typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;
extern int strcmp(const char *, const char *);

static inline char *textureName(char *object)
{
    char *texture = *(char **)(object + 0x20);
    int offset = 0;
    switch (*(int *)(texture + 0x1C) & 0x3F) {
    case 0x13:
    case 0x1B:
        offset = 0x400;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        offset = 0x40;
        break;
    }
    return texture + *(int *)(texture + 0x18) + offset;
}

static inline void *findTexture(void *namePointer)
{
    const char *name = namePointer;
    Node *node = D_00136274;
    char *result = 0;
    for (; node; node = node->next) {
        char *object = *(char **)((char *)node->a + 0x28);
        if (strcmp(name, textureName(object)) == 0) {
            result = object;
            break;
        }
    }
    return result;
}

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

static inline void scaleClutAlpha(TexObject *object, float scale)
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

void texScaleClutAlphaByName(void *name, float scale)
{
    void *object = findTexture(name);
    if (object)
        scaleClutAlpha(object, scale);
}
