typedef struct {
    unsigned long dmaTag;
    unsigned int vifCycle;
    unsigned int vifUnpack;
    float matrix[16];
    unsigned int command;
    unsigned int padding[3];
} MatrixPacket;

typedef struct {
    MatrixPacket packet[2];
    unsigned char *mesh;
    unsigned int padding[3];
} MeshInstance;

extern void *iosMallocAlign(void *, int, int);
extern void iosUnitMatrix(float *);

MeshInstance *meshCreateInstanceCopy(void *heap, unsigned char *mesh)
{
    MeshInstance *instance = iosMallocAlign(heap, sizeof(MeshInstance), 16);

    instance->mesh = mesh;
    instance->packet[0].dmaTag = 0x60000005;
    instance->packet[0].vifCycle = 0x01000101;
    instance->packet[0].vifUnpack = 0x6C048000;
    iosUnitMatrix(instance->packet[0].matrix);
    instance->packet[0].command = 0x15000006;
    instance->packet[0].padding[0] = 0;
    instance->packet[0].padding[1] = 0;
    instance->packet[0].padding[2] = 0;
    instance->packet[1] = instance->packet[0];
    return instance;
}
