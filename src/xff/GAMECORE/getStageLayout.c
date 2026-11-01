typedef struct { char pad[0xC]; void *layout; } ChipData;
typedef struct { ChipData *data[2]; int flags[2]; char pad10[8]; } ChipRow;
typedef struct { char pad[0x8]; ChipRow *rows; char padC[0x48 - 0xC]; int width; int height; } MapSize;
extern MapSize D_0017A340;

static inline int get_chip_no(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

void *getStageLayout(int x, int y, int layer)
{
    void *r;
    if (D_0017A340.rows[get_chip_no(x, y)].data[layer])
        r = D_0017A340.rows[get_chip_no(x, y)].data[layer]->layout;
    else
        r = 0;
    return r;
}
