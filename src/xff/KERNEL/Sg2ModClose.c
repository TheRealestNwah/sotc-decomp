typedef struct {
    int closed;
    char pad[0x9AC];
} Mod;

extern Mod B_000C5C28[];

int Sg2ModClose(int id)
{
    if (id >= 0) {
        B_000C5C28[id].closed = 1;
    }
    return 0;
}
