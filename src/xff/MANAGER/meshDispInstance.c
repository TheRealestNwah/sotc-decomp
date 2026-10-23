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

extern void iosDlLockObj(unsigned char *);
extern void iosDlChainTailCurrent(const void *);

static inline int *meshClass(unsigned char *mesh)
{
    if (mesh[8] != 0x23) {
        return 0;
    }
    return (int *)(mesh + 0x20);
}

void meshDispInstance(MeshInstance *instance)
{
    unsigned char *mesh = instance->mesh;
    int *m = meshClass(mesh);

    iosDlLockObj(mesh);
    iosDlChainTailCurrent(&instance->packet[m[4]]);
    {
        int *c = meshClass(mesh);

        c += c[4];
        iosDlChainTailCurrent((void *)*c);
    }
}
