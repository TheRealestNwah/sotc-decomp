typedef struct {
    unsigned long dmaTag;
    unsigned int vifCycle;
    unsigned int vifUnpack;
    float matrix[16];
    unsigned int command;
    unsigned int padding[3];
} MatrixPacket;

extern void *iosAllocPacketPtrPath1(int);
extern void iosCopyMatrix(void *, void *);
extern void iosDlChainTailCurrent(const void *);

void meshTransMatrix(void *matrix)
{
    MatrixPacket *packet = iosAllocPacketPtrPath1(0x60);

    packet->dmaTag = 0x60000005;
    packet->vifCycle = 0x01000101;
    packet->vifUnpack = 0x6C048000;
    iosCopyMatrix(packet->matrix, matrix);
    packet->command = 0x15000006;
    packet->padding[0] = 0;
    packet->padding[1] = 0;
    packet->padding[2] = 0;
    iosDlChainTailCurrent(packet);
}
