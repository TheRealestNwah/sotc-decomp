typedef struct { int v; char pad[0xDC]; } E;
extern E B_000DE3B8[];

int Sg2SlotGetVol(int i)
{
    return B_000DE3B8[i].v;
}
