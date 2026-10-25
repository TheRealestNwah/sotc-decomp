typedef struct TexWork {
    char pad0[0x40];
    int *clut;
    int *bank[2];
} TexWork;

typedef struct Texture {
    char pad0[0xC];
    TexWork *work;
    char pad10[0xC];
    int format;
} Texture;

typedef struct TexObject {
    char pad0[0x20];
    Texture *texture;
} TexObject;

extern const int RO_0013D5C0[];

void texClutReset(TexObject *object)
{
    Texture *texture = object->texture;
    TexWork *work = texture->work;
    int *clut = work->clut;
    int i;

    for (i = 0; i < 2; i++) {
        int *dest = work->bank[i];
        int j;
        for (j = 0; j < RO_0013D5C0[texture->format & 0x3F]; j++)
            dest[j] = clut[j];
    }
}
