typedef struct { int v; char pad[0xDC]; } E;
extern E B_000DE3C8[];

void Sg2SlotSetBendRange(int i, int v)
{
    B_000DE3C8[i].v = v;
}
