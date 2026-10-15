typedef struct { int used; char pad[0x28]; } Vab;
extern Vab B_000E2200[];

int get_vabid(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (B_000E2200[i].used == 0)
            return i;
    }
    return -1;
}
