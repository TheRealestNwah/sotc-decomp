/* The char member lets the packet stores alias the model fields, so the
   model stores stay after them, as in the original. */
typedef union {
    struct {
        unsigned long tag;
        float pad8;
        float padC;
        unsigned long reg;
        int pad18;
        int pad1C;
    } s;
    char alias;
} ShadowPacket;

typedef struct {
    char pad[0x10];
    unsigned int f10;
    int f14;
    float scale;
    ShadowPacket *packet;
} ShadowModel;

extern ShadowPacket *iosMallocAlign(void *, int, int);

void shadowModelInit(void *ptn, ShadowModel *model, float scale)
{
    ShadowPacket *p = iosMallocAlign(ptn, 0x20, 0x10);

    p->s.tag = (model->f14 >> 4) | 0x30000000 | ((unsigned long)model->f10 << 32);
    p->s.reg = 0x60000000;
    p->s.pad8 = 0;
    p->s.padC = 0;
    p->s.pad18 = 0;
    p->s.pad1C = 0;
    model->scale = scale;
    model->packet = p;
}
