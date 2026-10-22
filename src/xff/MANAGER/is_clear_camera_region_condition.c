typedef struct {
    int unk0;
    int objectId;
    int parentKind;
    int unkC;
} CameraRegionMetadata;

typedef struct {
    int type;
    char pad4[0xC];
    void *unk10;
    CameraRegionMetadata *metadata;
} CameraRegion;

static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

extern char *GetLayoutClass(void *);
extern void *GetLayoutParentObj(char *);
extern float *get_camera_direction(void *);
extern int is_parent_obj_boss_camera_region(CameraRegion *);
extern int func_000E7D48(float *, char *, CameraRegion *, void *);

int is_clear_camera_region_condition(float *pos, CameraRegion *region, void *arg, void *camera, int boss)
{
    int clear = 0;
    char *layout = GetLayoutClass(region->unk10);
    void *parent;
    float diff[4];

    if (!is_parent_obj_boss_camera_region(region) || boss == 1) {
        if (func_000E7D48(pos, layout, region, arg) == 1) {
            int kind = region->metadata->unkC;
            if (kind == 10000) {
                clear = 1;
            } else if (kind == 10001) {
                parent = GetLayoutParentObj(layout);
                if (parent != 0) {
                    vecSubXYZ(diff, *(float **)(GetLayoutClass(parent) + 0x134), pos);
                    if (vecDot(diff, get_camera_direction(camera)) <= 0.0f)
                        clear = 1;
                }
            }
        }
    }
    return clear;
}
