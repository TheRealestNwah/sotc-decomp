typedef struct VabHeader {
    unsigned char unknown00[0x3C];
    unsigned short *seseq;
} VabHeader;
typedef struct Vab {
    unsigned char unknown00[0x14];
    VabHeader *header;
    unsigned char unknown18[0x14];
} Vab;
extern Vab B_000E2200[];
extern int vab_check_alive(int);

void *vab_get_seseq(int bank, unsigned int program, unsigned int sequence)
{
    Vab *vab = &B_000E2200[bank];
    unsigned short *chunk;
    unsigned int offset;
    if (!vab_check_alive(bank))
        return 0;
    if (vab->header == 0)
        return 0;
    chunk = vab->header->seseq;
    if (chunk == 0)
        return 0;
    if (chunk[0] < program)
        return 0;
    offset = chunk[program + 1] >> 1;
    if (chunk[offset] < sequence)
        return 0;
    return (char *)chunk + chunk[offset + sequence + 1];
}
