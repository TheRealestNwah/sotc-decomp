typedef union {
    unsigned long d;
    unsigned int w[2];
} Word64;

typedef struct {
    char pad0[0x38];
    int mode;
} ModelWork;

typedef struct {
    char pad0[0x18];
    Word64 flags;
    char pad20[0x100];
} ModelLayer;

typedef struct {
    char pad0[0x8];
    ModelWork *work;
} Model;

#define BIT(f, n) ((int)((f) >> (n)) & 1)

int modelGetDlLayer(Model *model, ModelLayer *layer, int alpha)
{
    int mode = model->work != 0 ? model->work->mode : 0;
    unsigned long f = layer->flags.d;

    if (f & 0x01020000) {
        return 8;
    }
    if (BIT(f, 23)) {
        return 10;
    }
    if (BIT(f, 25)) {
        return 16;
    }
    if (BIT(f, 9)) {
        return 17;
    }
    if (BIT(f, 10)) {
        if (BIT(f, 8) || alpha) {
            return 13;
        }
        return 12;
    }
    if (BIT(f, 14)) {
        return 1;
    }
    if (BIT(f, 15)) {
        return 18;
    }
    if (BIT(f, 8) || alpha) {
        return mode == 1 ? 6 : 3;
    }
    return mode == 1 ? 5 : 2;
}
