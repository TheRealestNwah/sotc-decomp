typedef struct {
    char pad0[0x28];
    void *packet;
} ModelClassData;

typedef struct {
    char pad0[0xC];
    ModelClassData *data;
} ModelClassRef;

typedef struct {
    char pad0[0x10];
    union {
        ModelClassRef *ref;
        void *packet;
    } u;
    char pad14[0xC];
} ModelPart;

typedef struct {
    char pad0[0x18];
    unsigned long flags;
    char pad20[0x40];
    char surface[0x60];
    char layer[0x60];
} ModelLayer;

typedef union {
    unsigned long d;
    unsigned int w[2];
} Word64;

typedef struct {
    Word64 tag0;
    char pad8[0x18];
    Word64 tag1;
    char pad28[0x18];
} LayerPacket;

typedef struct {
    Word64 tag;
    unsigned long pad8;
    Word64 dma;
    Word64 direct;
    char pad20[0x10];
} DrawPacket;

typedef struct {
    DrawPacket *draw;
    LayerPacket *layers;
} ModelPacketSet;

typedef struct {
    unsigned int addr;
    char pad4[0x4];
    int layer;
    char padC[0x4];
    unsigned int size;
    char pad14[0x8];
    DrawPacket *packet;
} ModelDraw;

typedef struct {
    char pad0[0x14];
    ModelPacketSet *packetSet;
    char pad18[0x28];
    ModelPart *parts;
    unsigned int partCount;
    char pad48[0x8];
    ModelLayer *layers;
    unsigned int layerCount;
    char pad58[0x8];
    ModelDraw *draws;
    unsigned int drawCount;
} Model;

extern int func_0001B340(Model *, ModelLayer *);

int modelReInitialize(void *heap, Model *model)
{
    ModelPacketSet *packetSet = model->packetSet;
    DrawPacket *draw = packetSet->draw;
    ModelDraw *d;
    unsigned int i;

    for (i = 0; i < model->layerCount; i++) {
        ModelLayer *layer = &model->layers[i];
        LayerPacket *p = &packetSet->layers[i];
        unsigned long f;

        p->tag0.d = ((unsigned long)(int)layer->surface << 32) | 0x50000000;
        f = layer->flags;
        if (((int)(f >> 25) & 1) || (f & 0x2200) == 0x2200) {
            p->tag1.d = ((unsigned long)(int)layer->layer << 32) | 0x50000000;
        }
    }
    d = model->draws;
    for (i = 0; i < model->drawCount; i++) {
        ModelLayer *layer = &model->layers[d->layer];

        draw->tag.d = ((unsigned long)(int)layer->surface << 32) | 0x50000000;
        draw->dma.d = (unsigned int)((d->addr >> 4) | 0x30000000) | ((unsigned long)d->size << 32);
        draw->direct.w[0] = func_0001B340(model, layer) | 0x14000000;
        d->packet = draw;
        d++;
        draw++;
    }
    for (i = 0; i < model->partCount; i++) {
        model->parts[i].u.packet = model->parts[i].u.ref->data->packet;
    }
    return 1;
}
