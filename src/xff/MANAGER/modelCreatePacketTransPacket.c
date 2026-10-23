typedef union {
    unsigned long d;
    unsigned int w[2];
} Word64;

typedef struct {
    char pad0[0x18];
    Word64 flags;
    char pad20[0x40];
    char surface[0x60];
    char layer[0x4C];
    unsigned int alpha;
    char pad110[0x10];
} ModelLayer;

typedef struct {
    Word64 tag0;
    unsigned int w8;
    unsigned int wC;
    Word64 tag0b;
    unsigned int w18;
    unsigned int w1C;
    Word64 tag1;
    unsigned int w28;
    unsigned int w2C;
    Word64 tag1b;
    unsigned int w38;
    unsigned int w3C;
} LayerPacket;

typedef struct {
    Word64 tag;
    unsigned int w8;
    unsigned int wC;
    Word64 dma;
    Word64 direct;
    Word64 end;
    unsigned int w28;
    unsigned int w2C;
} DrawPacket;

typedef struct {
    union {
        DrawPacket *p;
        unsigned int a;
    } draw;
    union {
        LayerPacket *p;
        unsigned int a;
    } layers;
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
    char pad18[0x38];
    ModelLayer *layers;
    unsigned int layerCount;
    char pad58[0x8];
    ModelDraw *draws;
    unsigned int drawCount;
} Model;

extern void *iosMallocAlign(void *, int, int);
extern int func_0001B340(Model *, ModelLayer *);

void modelCreatePacketTransPacket(void *heap, Model *model)
{
    ModelPacketSet *packetSet;
    ModelDraw *d;
    unsigned int i;

    packetSet = iosMallocAlign(heap, 8, 16);
    model->packetSet = packetSet;
    packetSet->layers.p = iosMallocAlign(heap, model->layerCount * 0x40, 16);
    for (i = 0; i < model->layerCount; i++) {
        ModelLayer *layer = &model->layers[i];
        LayerPacket *p = &packetSet->layers.p[i];
        unsigned long f;

        p->w8 = 0;
        p->wC = 0;
        p->tag0.d = ((unsigned long)(int)layer->surface << 32) | 0x50000000;
        p->tag0b.d = 0x60000000;
        p->w18 = 0;
        p->w1C = 0;
        f = layer->flags.d;
        if (((int)(f >> 25) & 1) || (f & 0x2200) == 0x2200) {
            p->tag1.d = ((unsigned long)(int)layer->layer << 32) | 0x50000000;
            p->w28 = 0;
            p->w2C = 0;
            p->tag1b.d = 0x60000000;
            p->w38 = 0;
            p->w3C = 0;
        }
        layer->alpha = layer->alpha * 255 / 128;
    }
    packetSet->draw.p = iosMallocAlign(heap, model->drawCount * 0x30, 16);
    d = model->draws;
    for (i = 0; i < model->drawCount; i++) {
        ModelLayer *layer = &model->layers[d->layer];
        DrawPacket *draw = &packetSet->draw.p[i];

        draw->w8 = 0;
        draw->wC = 0;
        draw->tag.d = ((unsigned long)(int)layer->surface << 32) | 0x50000000;
        draw->dma.d = (unsigned int)((d->addr >> 4) | 0x30000000) | ((unsigned long)d->size << 32);
        draw->direct.w[0] = func_0001B340(model, layer) | 0x14000000;
        draw->direct.w[1] = 0;
        draw->end.d = 0x60000000;
        draw->w28 = 0;
        draw->w2C = 0;
        d->packet = draw;
        d++;
    }
}
