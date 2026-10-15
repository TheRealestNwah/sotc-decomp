extern int B_00149928[];
extern void *MicroCode[];
extern int iosDlGetLayer(void);
extern void iosDlChainTailCurrent(const void *);
extern const unsigned int RO_001407C0[];

void transMicroCodeWithFlush(int id)
{
    int l = iosDlGetLayer();
    iosDlChainTailCurrent(RO_001407C0);
    if (B_00149928[l] != id) {
        iosDlChainTailCurrent(MicroCode[id]);
        B_00149928[l] = id;
    }
}

