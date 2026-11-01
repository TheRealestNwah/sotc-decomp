typedef struct {
    char unknown00[0xC];
    int magic;
    int offset[6];
    char unknown28[8];
    int chunk[6];
    char unknown48[0x34];
    int unknown7C;
} VabHeader;

typedef struct {
    int alive;
    int hd;
    char unknown08[8];
    int unknown10;
    VabHeader *header;
    int progCount;
    unsigned short *progTable;
    int splitCount;
    unsigned short *splitChunk;
    unsigned short *splitTable;
} Vab;

#define RELOCATE(hd, n) \
    if ((hd)->offset[n] != -1) \
        (hd)->chunk[n] = (hd)->offset[n] + (int)(hd); \
    else \
        (hd)->chunk[n] = 0

static int func_0002D5A8(Vab *vab, VabHeader *hd)
{
    if (hd->magic != 0x64685353)
        return -1;
    if (vab->alive == 0) {
        if (hd->unknown7C == -1)
            vab->alive = 3;
        else
            vab->alive = 4;
        vab->hd = (int)hd;
        RELOCATE(hd, 0);
        RELOCATE(hd, 1);
        RELOCATE(hd, 2);
        RELOCATE(hd, 3);
        RELOCATE(hd, 4);
        RELOCATE(hd, 5);
        vab->header = hd;
        if (hd->chunk[1] != 0) {
            vab->progCount = *(unsigned short *)hd->chunk[1];
            vab->progTable = (unsigned short *)hd->chunk[1] + 1;
        } else {
            vab->progCount = -1;
            vab->progTable = 0;
        }
        if (hd->chunk[2] != 0) {
            vab->splitCount = *(unsigned short *)hd->chunk[2];
            vab->splitChunk = (unsigned short *)hd->chunk[2];
            vab->splitTable = (unsigned short *)hd->chunk[2] + 1;
        } else {
            vab->splitCount = -1;
            vab->splitTable = 0;
        }
        vab->unknown10 = 0x7F;
        return 0;
    }
    return -1;
}
