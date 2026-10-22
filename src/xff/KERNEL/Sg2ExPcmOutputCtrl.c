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
} PcmOutput;

extern PcmOutput B_000E2360;
extern int Sg2StPcmStart(int, int);
extern int Sg2StPcmStop(void);

void Sg2ExPcmOutputCtrl(int mode)
{
    if ((mode & 3) == 3)
        return;
    if (mode & 1) {
        if (!(B_000E2360.mode & 1)) {
            B_000E2360.x18 = 0;
            if (B_000E2360.x1A4 != 0 && B_000E2360.buffer != 0)
                Sg2StPcmStart(B_000E2360.x1A4, B_000E2360.x1A8 * 2);
        }
    }
    if (mode & 2)
        Sg2StPcmStop();
    B_000E2360.mode = mode;
}
