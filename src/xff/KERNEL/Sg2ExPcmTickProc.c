typedef struct {
    int unknown00;
    int mode;
    int unknown08;
    void *buffer;
    char padding10[8];
    int x18;
    char padding1C[0x188];
    int x1A4;
    int x1A8;
    int unknown1AC;
    int halfIndex;
} PcmOutput;
extern PcmOutput B_000E2360;
extern int Sg2StPcmIopTransOffset(void);
static void func_0002EAE0(void);
static void func_0002E498(PcmOutput *, int);
static void func_0002E5A0(PcmOutput *, int);

void Sg2ExPcmTickProc(void)
{
    int offset;
    int half;
    func_0002EAE0();
    if (!(B_000E2360.mode & 2)) {
        offset = Sg2StPcmIopTransOffset();
        half = B_000E2360.x1A8 / 2;
        if ((offset / 2) / half != B_000E2360.halfIndex) {
            func_0002E498(&B_000E2360, half);
            func_0002E5A0(&B_000E2360, half);
            B_000E2360.halfIndex = (B_000E2360.halfIndex + 1) % 2;
        }
    }
}
