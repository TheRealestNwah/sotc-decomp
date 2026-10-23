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

typedef union {
    unsigned long d;
    unsigned int w[2];
} Word64;

typedef struct {
    char pad0[0x18];
    Word64 flags;
    char pad20[0x100];
} ModelLayer;

typedef struct {
    char pad0[0x8];
    void *work;
    char padC[0xC];
    unsigned long flags;
    char pad20[0x20];
    ModelPart *parts;
    unsigned int partCount;
    char pad48[0x8];
    ModelLayer *layers;
    unsigned int layerCount;
} Model;

extern void modelCreatePacketTransPacket(void *, Model *, void *);

int modelInitialize(void *heap, Model *model, void *work)
{
    unsigned int i;

    modelCreatePacketTransPacket(heap, model, work);
    model->work = work;
    for (i = 0; i < model->partCount; i++) {
        model->parts[i].u.packet = model->parts[i].u.ref->data->packet;
    }
    model->flags &= ~0x180;
    for (i = 0; i < model->layerCount; i++) {
        model->layers[i].flags.d &= ~0xC0000000UL;
    }
    return 1;
}
