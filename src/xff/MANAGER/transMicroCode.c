extern int B_00149928[];
extern void *MicroCode[];
extern int iosDlGetLayer(void);
extern void iosDlChainTailCurrent(const void *);
static const unsigned int RO_001407C0[4] __attribute__((aligned(16))) = { 0x60000000, 0, 0x13000000, 0 };

void transMicroCode(int id)
{
    int l = iosDlGetLayer();
    iosDlChainTailCurrent(RO_001407C0);
    if (B_00149928[l] != id) {
        iosDlChainTailCurrent(MicroCode[id]);
        B_00149928[l] = id;
    }
}
