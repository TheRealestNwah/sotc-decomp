typedef struct { int v; char pad[0xDC]; } E;
extern E B_000DE3C4[];

int Sg2SlotGetPan(int i)
{
    return B_000DE3C4[i].v;
}
