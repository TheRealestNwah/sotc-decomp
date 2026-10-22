typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float v[4];
} __attribute__((aligned(16))) Vec4;

typedef struct {
    int unk0;
    int objectId;
    int parentKind;
    int unkC;
    int priority;
    float hitOffset;
} CameraRegionMetadata;

typedef struct {
    int unk0;
    int shape;
    char pad8[8];
    void *unk10;
    CameraRegionMetadata *metadata;
    char pad18[8];
    Vec4 region;
} CameraRegion;

static inline void vecAddXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

extern int is_have_region_camera_region(CameraRegion *);
extern int IsInsideOfRegion(int, float *, void *, Vec4 *, float, float, float);

static int func_000E7D48(float *pos, char *layout, CameraRegion *region, CameraRegion *other)
{
    int inside = 0;
    if (is_have_region_camera_region(region) == 1) {
        CameraRegionMetadata *meta = region->metadata;
        Vec4 center;
        if (other != 0 && region->unk10 == other->unk10) {
            Vec4 offset;
            Vec4 tmp;
            tmp.v[0] = meta->hitOffset;
            tmp.v[1] = meta->hitOffset;
            tmp.v[2] = meta->hitOffset;
            tmp.v[3] = 0.0f;
            offset = tmp;
            vecAddXYZ(&center, (Vec4 *)(layout + 0x90), &offset);
        } else {
            *(s128 *)&center = *(s128 *)(layout + 0x90);
        }
        switch (region->shape) {
        case 0x27:
            inside = IsInsideOfRegion(0, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        case 0x28:
            inside = IsInsideOfRegion(3, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        case 0x29:
            inside = IsInsideOfRegion(2, pos, *(void **)(layout + 0x134), &region->region, 2.0f, center.v[0], center.v[1]);
            break;
        case 0x2A:
            inside = IsInsideOfRegion(1, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        }
    }
    return inside;
}
