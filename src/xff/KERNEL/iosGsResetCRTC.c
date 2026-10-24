typedef struct {
    unsigned int b0 : 1;
    unsigned int pad1 : 4;
    unsigned int b5 : 1;
    unsigned int rest : 26;
} CrtcBits;

typedef struct {
    char pad0[8];
    CrtcBits bits;
    char pad1[0x38 - 0xC];
} CrtcEntry;

typedef struct {
    char pad0[0x10];
    CrtcEntry entry[2];
    char pad1[0xA0 - 0x80];
    int mode;
} CrtcWork;

extern CrtcWork B_00065550;
extern void func_00014BD8(void);

void iosGsResetCRTC(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        B_00065550.entry[i].bits.b0 = B_00065550.mode;
        B_00065550.entry[i].bits.b5 = B_00065550.mode;
    }
    func_00014BD8();
}
