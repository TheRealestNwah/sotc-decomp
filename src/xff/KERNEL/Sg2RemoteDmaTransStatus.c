typedef struct { int v; char pad[0x10]; } E;
extern E B_000DD490[];

int Sg2RemoteDmaTransStatus(int i)
{
    return B_000DD490[i].v;
}
