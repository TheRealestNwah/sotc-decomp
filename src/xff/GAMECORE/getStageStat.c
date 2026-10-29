typedef struct { unsigned int lo : 4; unsigned int hi : 28; } ChipFlags;
typedef struct { void *data[2]; ChipFlags flags[2]; char pad10[8]; } ChipRow;
typedef struct { char pad[0x48]; int width; int height; } MapSize;
extern MapSize D_0017A340;
extern ChipRow *D_0017A348;

static inline int get_chip_no(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int get_chip_state(int layer, int group)
{
    if (group != -1)
        return D_0017A348[group].flags[layer].lo;
    return 7;
}

int getStageStat(int x, int y, int layer)
{
    return get_chip_state(layer, get_chip_no(x, y));
}
