typedef struct { int a; unsigned short adsr1; unsigned short adsr2; char pad[0xD8]; } Sg2Slot;
extern Sg2Slot B_000DE3D0[];
extern int Sg2RemoteSend(int, int, int, int);

int Sg2SlotSetAdsr(int i, unsigned short a1, unsigned short a2)
{
    Sg2Slot *s = &B_000DE3D0[i];
    s->adsr1 = a1;
    s->adsr2 = a2;
    return Sg2RemoteSend(2, i, a1, a2);
}
