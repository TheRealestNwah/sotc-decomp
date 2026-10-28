typedef struct { int mode; int a, b, c, d; int x14; char pad[0x1B8]; int x1d0; } PcmIn;
extern PcmIn B_000E2518[];
extern int DIntr(void);
extern int EIntr(void);

void Sg2ExPcmInputCtrl(unsigned int ch, unsigned int mode)
{
    int s;
    if (ch < 4 && (mode & 3) != 3) {
        s = DIntr();
        if (mode & 1) {
            B_000E2518[ch].x14 = 0;
            B_000E2518[ch].x1d0 = 0;
        }
        B_000E2518[ch].mode = mode;
        if (s) {
            EIntr();
            s = 0;
        }
    }
}
