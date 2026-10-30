typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

typedef struct {
    Vec4 points[10];
    int count;
    float rate;
    char unknownA8[8];
} Track;

typedef struct {
    Track tracks[3];
    Vec4 unknown210;
    Vec4 unknown220;
    Vec4 unknown230;
    int unknown240;
    int unknown244;
} TrackSet;

#define VU_SET_IDENTITY(p) __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(p) : "memory")

static inline void initTrack(Track *t)
{
    VU_SET_IDENTITY(&t->points[0]);
    VU_SET_IDENTITY(&t->points[1]);
    VU_SET_IDENTITY(&t->points[2]);
    VU_SET_IDENTITY(&t->points[3]);
    VU_SET_IDENTITY(&t->points[4]);
    VU_SET_IDENTITY(&t->points[5]);
    VU_SET_IDENTITY(&t->points[6]);
    VU_SET_IDENTITY(&t->points[7]);
    VU_SET_IDENTITY(&t->points[8]);
    VU_SET_IDENTITY(&t->points[9]);
    t->count = 0;
    t->rate = 1.0f / 29.97f;
}

static void func_00044BD0(TrackSet *set)
{
    initTrack(&set->tracks[0]);
    initTrack(&set->tracks[1]);
    initTrack(&set->tracks[2]);
    VU_SET_IDENTITY(&set->unknown220);
    VU_SET_IDENTITY(&set->unknown230);
    VU_SET_IDENTITY(&set->unknown210);
    set->unknown240 = 0;
    set->unknown244 = 0;
}
