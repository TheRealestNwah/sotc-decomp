/* Unlinks a seamless stage object whose chip state is 3 or 6; returns 1 if it did. */
typedef struct SeamlessObj {
    int x;
    int y;
    int z;
    char padC[0x14 - 0xC];
    struct SeamlessObj *prev;
    struct SeamlessObj *next;
} SeamlessObj;

typedef struct {
    char pad0[8];
    int flags[4];
} ChipRow;

typedef struct {
    char pad0[8];
    ChipRow *chips;
    char padC[0x48 - 0xC];
    int width;
    int height;
} StageMap;

extern StageMap D_0017A340;
extern ChipRow *D_0017A348;
extern int D_0017A3D0;
extern SeamlessObj *D_0017A3D4;

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int getChipState(int no, int z)
{
    int s;

    if (no != -1)
        s = D_0017A348[no].flags[z] & 0xF;
    else
        s = 7;
    return s;
}

static int func_0001EC38(SeamlessObj *o)
{
    int no = getChipNo(o->x, o->y);
    SeamlessObj *prev;
    SeamlessObj *next;

    if (getChipState(no, o->z) == 3 || getChipState(no, o->z) == 6) {
        prev = o->prev;
        next = o->next;
        if (o == D_0017A3D4)
            D_0017A3D4 = next;
        if (prev != 0)
            prev->next = next;
        if (next != 0)
            next->prev = prev;
        D_0017A3D0--;
        return 1;
    }
    return 0;
}
