typedef union {
    unsigned long d;
    unsigned int w[2];
} Word64;

typedef struct {
    char pad0[0x10];
    void *texture;
    char pad14[0xC];
} ModelPart;

typedef struct {
    char pad0[0x18];
    Word64 flags;
    char pad20[0xC];
    int texture;
    char pad30[0xC];
    int texture2;
    char pad40[0xE0];
} ModelLayer;

typedef struct {
    char pad0[0x4];
    char *packets;
} ModelPacketSet;

typedef struct {
    char pad0[0x14];
    ModelPacketSet *packetSet;
    char pad18[0x28];
    ModelPart *parts;
    char pad44[0xC];
    ModelLayer *layers;
} Model;

#define BIT(f, n) ((int)((f) >> (n)) & 1)

extern ModelLayer **D_001360B8;

extern int iosDlGetLayer();
extern void texTransRequest(void *, int, int);
extern void texTransRequestMulti(void *, void *, int);
extern void iosDlChainTailCurrent(void *);

void modelSetSurface(Model *model, int index)
{
    ModelPacketSet *packetSet = model->packetSet;
    ModelLayer *layer = &model->layers[index];
    int dl = iosDlGetLayer();

    if (layer != D_001360B8[dl]) {
        if (BIT(layer->flags.d, 5) || layer->flags.w[1] == 2) {
            texTransRequestMulti(model->parts[layer->texture].texture, model->parts[layer->texture2].texture, 0);
        } else if (layer->flags.w[1] == 1) {
            texTransRequest(model->parts[layer->texture].texture, 0, 0);
        }
        D_001360B8[dl] = layer;
    }
    iosDlChainTailCurrent(packetSet->packets + index * 0x40);
}
