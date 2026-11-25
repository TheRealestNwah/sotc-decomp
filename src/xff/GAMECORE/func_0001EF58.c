/* Visibility test for map chip (x, y) on layer z: only chips whose state is 0 or 5 qualify. By group kind: kind 1 is visible when it shares its group with the chip at (ox, oy); kinds 2 and 3 additionally need the same group or chip +0x14 set, then pass the range test; kinds 0, 4 and 5 take the range test alone. The range test (VIEW) on layer 0 checks |d + 0.5| <= D_0017A314 on both axes around (cx, cy); on other layers the chip must lie outside that square but inside the one of D_0017A314 + D_0017A318. ABS evaluates its argument twice, as in the Original. */
typedef struct { int kind; } Grp;
typedef struct { int data[2]; int flags[2]; Grp *grp; int f14; } ChipRow;
typedef struct { char pad0[8]; ChipRow *chips; char padC[0x3C]; int width; int height; } StageMap;

extern StageMap D_0017A340;
extern ChipRow *D_0017A348;
extern int D_0017A314;
extern int D_0017A318;

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

#define ABS(a) ((a) < 0.0f ? -(a) : (a))
#define inRange(dx, dy, r) (ABS((float)(dx) + 0.5f) <= (float)(r) && ABS((float)(dy) + 0.5f) <= (float)(r))

#define VIEW                                                     \
    if (z == 0) {                                                \
        if (inRange(x - cx, y - cy, D_0017A314))                 \
            return 1;                                            \
    } else {                                                     \
        if (!inRange(x - cx, y - cy, D_0017A314) &&              \
            inRange(x - cx, y - cy, D_0017A314 + D_0017A318))    \
            return 1;                                            \
    }

static int func_0001EF58(int x, int y, int z, int cx, int cy, int ox, int oy)
{
    int no = getChipNo(x, y);
    Grp *g;
    int kind;

    if (no < 0)
        return 0;
    if (getChipState(no, z) == 0 || getChipState(no, z) == 5) {
        g = D_0017A340.chips[no].grp;
        kind = g != 0 ? g->kind : 0;
        switch (kind) {
        case 1:
            if (D_0017A340.chips[no].grp == D_0017A340.chips[getChipNo(ox, oy)].grp)
                return 1;
            break;
        case 2:
        case 3:
            if (D_0017A340.chips[no].grp != D_0017A340.chips[getChipNo(ox, oy)].grp && D_0017A340.chips[no].f14 == 0)
                break;
            VIEW;
            break;
        case 0:
        case 4:
        case 5:
            VIEW;
            break;
        }
    }
    return 0;
}
