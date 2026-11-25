/* Seamless stage chip load request: for chip (x, y) whose layer state is 3 (loaded) or 6 (pending), marks it 4 and starts the T_0001F8E8 loader script with a request {layer, chip, 0, state == 6}, then refreshes the neighbourhood through func_0001F838. */
typedef struct { unsigned int lo : 4; unsigned int hi : 28; } ChipFlags;
typedef struct { int data[2]; ChipFlags flags[2]; char pad10[8]; } ChipRow;
typedef struct { char pad0[8]; int chips; char padC[0x3C]; int width; int height; } MapSize;

extern MapSize D_0017A340;
extern char rootPtn[];
extern char gcGlobalVar[];
extern int *iosMallocAlign(void *, int, int);
extern void createScriptObj(void *, void *, int, int, int, int, int, int);
extern void T_0001F8E8(void);
extern void func_0001F838(int, int);

static inline int get_chip_no(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int get_chip_state(int layer, int group)
{
    if (group != -1)
        return ((ChipRow *)D_0017A340.chips)[group].flags[layer].lo;
    return 7;
}

static void func_0001FA68(int layer, int x, int y)
{
    int chip = get_chip_no(x, y);
    int *p;

    if (get_chip_state(layer, chip) != 3 && get_chip_state(layer, chip) != 6)
        return;
    p = iosMallocAlign(rootPtn, 0x10, 0x10);
    p[0] = layer;
    p[1] = chip;
    p[2] = 0;
    p[3] = get_chip_state(layer, chip) == 6;
    ((ChipRow *)D_0017A340.chips)[chip].flags[layer].lo = 4;
    createScriptObj(T_0001F8E8, p, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
    func_0001F838(x, y);
}
