typedef struct { int ssa; char pad[0xDC]; } Sg2Slot;
extern Sg2Slot B_000DE3D0[];
extern void Sg2RemoteSend(int, int, int, int);

int Sg2SlotSetSsa(int i, int ssa)
{
    B_000DE3D0[i].ssa = ssa;
    Sg2RemoteSend(3, i, ssa, 0);
}
