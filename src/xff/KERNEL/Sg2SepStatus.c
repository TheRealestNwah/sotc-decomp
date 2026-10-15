typedef struct {
    int status;
    char pad[0x4C];
} Sep;

extern Sep B_000DD700[];

int Sg2SepStatus(unsigned int id)
{
    if (id < 0x20) {
        return B_000DD700[id].status;
    }
    return 0;
}
