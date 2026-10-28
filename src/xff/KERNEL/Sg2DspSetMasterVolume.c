typedef struct { int v; char pad[0x14]; } E;
extern E B_000C5B08[];
extern int DIntr();
extern int EIntr(void);
extern void Sg2RemoteSend(int, int, int, int);

void Sg2DspSetMasterVolume(int i, int l, int r)
{
    int intr;

    intr = DIntr();
    B_000C5B08[i].v = l;
    Sg2RemoteSend(6, i, l, r);
    if (intr != 0) {
        EIntr();
    }
}
