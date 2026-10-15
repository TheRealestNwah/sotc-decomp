typedef struct {
    int status;
    char pad[0x7C];
} Smfp;

extern Smfp B_000E0DC0[];

int Sg2SmfpStatus(int id)
{
    if (id >= 0) {
        return B_000E0DC0[id].status;
    }
    return 1;
}
