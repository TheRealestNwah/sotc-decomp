typedef struct {
    char pad[0x40];
    float chip_w;
    float chip_d;
    char pad48[8];
    float origin_x;
    float origin_z;
} StageInfo;

/* The char member lets the id stores alias the position, so pos[2] is
   loaded after *x is written, as in the original. */
typedef union {
    int i;
    char alias;
} ChipID;

extern StageInfo D_0017A340;

static inline int roundChip(float f)
{
    int i = f;
    int r;

    if (f - (float)i < 0.5f)
        r = i;
    else if (f < 0.0f)
        r = i - 1;
    else
        r = i + 1;
    return r;
}

void getStageChipID(float *pos, ChipID *x, ChipID *z)
{
    x->i = roundChip((-pos[0] - D_0017A340.origin_x) / D_0017A340.chip_w);
    z->i = roundChip((-pos[2] - D_0017A340.origin_z) / D_0017A340.chip_d);
}
