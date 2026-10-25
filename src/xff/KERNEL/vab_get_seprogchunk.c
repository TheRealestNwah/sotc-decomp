typedef struct {
    char pad[0x44];
    unsigned short *seprogchunk;
} VabHeader;

typedef struct {
    char pad[0x14];
    VabHeader *header;
    char pad2[0x14];
} Vab;

extern Vab B_000E2200[];
extern int vab_check_alive(int);

void *vab_get_seprogchunk(int i, unsigned int prog)
{
    Vab *vab = &B_000E2200[i];
    unsigned short *chunk;

    if (!vab_check_alive(i)) {
        return 0;
    }
    if (vab->header == 0) {
        return 0;
    }
    chunk = vab->header->seprogchunk;
    if (chunk == 0) {
        return 0;
    }
    if ((int)chunk & 1) {
        return 0;
    }
    if (chunk[0] < prog) {
        return 0;
    }
    return (char *)chunk + chunk[prog + 1];
}
