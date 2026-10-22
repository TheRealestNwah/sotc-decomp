typedef struct {
    unsigned long dmaTag;
    unsigned int vifCycle;
    unsigned int vifUnpack;
    float matrix[2][16];
    unsigned int command;
    unsigned int padding[3];
} LightMatrixPacket;

extern void *iosAllocPacketPtrPath1(int);
extern void iosCopyMatrix(void *, void *);
extern void iosDlChainTailCurrent(const void *);

void meshTransLightMatrix(void *first, void *second)
{
    LightMatrixPacket *packet = iosAllocPacketPtrPath1(0xA0);


    packet->vifCycle = 0x01000101;
    packet->vifUnpack = 0x6C0803D8;
    packet->dmaTag = 0x60000009;
    iosCopyMatrix(packet->matrix[0], first);
    iosCopyMatrix(packet->matrix[1], second);
    packet->command = 0x14000002;
    packet->padding[0] = 0;
    packet->padding[1] = 0;
    packet->padding[2] = 0;
    iosDlChainTailCurrent(packet);
}

