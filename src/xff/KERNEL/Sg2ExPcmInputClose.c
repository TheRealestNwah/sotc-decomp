typedef struct { int a; int b; void *buf; char pad[0x1C8]; } PcmIn;
extern PcmIn B_000E2518[];
extern int DIntr(void);
extern void EIntr(void);
extern void Sg2ExPcmInputCtrl(unsigned int, int);
extern void free(void *);

void Sg2ExPcmInputClose(unsigned int ch)
{
    int s;
    if (ch < 4) {
        s = DIntr();
        Sg2ExPcmInputCtrl(ch, 2);
        free(B_000E2518[ch].buf);
        B_000E2518[ch].b = 0;
        B_000E2518[ch].buf = 0;
        if (s) {
            EIntr();
            s = 0;
        }
    }
}
