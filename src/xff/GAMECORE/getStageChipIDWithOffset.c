typedef struct {
    char pad[0x38];
    int num_x;
    int num_z;
    float chip_w;
    float chip_d;
    char pad48[8];
    float origin_x;
    float origin_z;
} StageInfo;

/* The char member lets the offset stores alias the chip ids, so they are
   reloaded, as in the original. */
typedef union {
    int i;
    char alias;
} ChipID;

extern StageInfo D_0017A340;

void getStageChipIDWithOffset(float *pos, ChipID *x, ChipID *z, float *ox, float *oz)
{
    float fx = (-pos[0] - D_0017A340.origin_x) / D_0017A340.chip_w;
    float fz = (-pos[2] - D_0017A340.origin_z) / D_0017A340.chip_d;

    x->i = fx;
    z->i = fz;
    *ox = fx - x->i;
    *oz = fz - z->i;
}
