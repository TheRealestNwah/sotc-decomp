typedef struct { int v; char pad[0xDC]; } E;
extern E B_000DE38C[];

void Sg2SlotSetGroup(int i, int v)
{
    B_000DE38C[i].v = v;
}
