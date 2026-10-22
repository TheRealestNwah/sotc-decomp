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
extern char *GetLayoutClass(void *);
extern void DEBUG_disp_region_object(int, void *, Vec4 *, Vec4 *, void *, float, float, float);
extern void glDrawNull(float, void *, Vec4 *, void *);
extern void glDrawLineArrow(void *, Vec4 *, Vec4 *, void *, float, float);

void disp_camera_region(CameraRegion *region, void *mode, int count, float alpha)
{
    if (is_have_region_camera_region(region) == 1) {
        Vec4 *rot = &region->region;
        float colors[3][4] __attribute__((aligned(16))) = { { 0.0f, 1.0f, 1.0f, alpha }, { 1.0f, 0.2f, 0.2f, alpha }, { 0.2f, 1.0f, 0.2f, alpha } };
        char *layout;
        Vec4 dir;
        int i;

        layout = GetLayoutClass(region->unk10);
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                             "vmul.xyzw vf5, vf4, vf4
"
                             "vmr32.xyzw vf6, vf4
"
                             "vmul.xyzw vf7, vf6, vf4
"
                             "vmr32.xyzw vf6, vf6
"
                             "vmul.xyzw vf8, vf6, vf4
"
                             "vsubx.z vf6, vf0, vf5x
"
                             "vsuby.z vf6, vf6, vf5y
"
                             "vaddw.y vf6, vf7, vf7w
"
                             "vsuby.x vf6, vf8, vf8y
"
                             "vsub.w vf6, vf0, vf0
"
                             "vadd.w vf5, vf0, vf0
"
                             "vmulw.xyz vf6, vf6, vf5w
"
                             "vaddw.z vf6, vf6, vf0w
"
                             "sqc2 vf6, 0x0(%0)
"
                             : : "r"(&dir), "r"(rot) : "memory");
        if (count > 2)
            count = 2;
        for (i = 0; i < count; i++) {
            Vec4 color;
            Vec4 center;
            if (i == 0)
                *(s128 *)&color = *(s128 *)&colors[0];
            else
                *(s128 *)&color = *(s128 *)&colors[1];
            if (i == 0) {
                *(s128 *)&center = *(s128 *)(layout + 0x90);
            } else {
                CameraRegionMetadata *meta = region->metadata;
                Vec4 offset;
                Vec4 tmp;
                tmp.v[0] = meta->hitOffset;
                tmp.v[1] = meta->hitOffset;
                tmp.v[2] = meta->hitOffset;
                tmp.v[3] = 0.0f;
                offset = tmp;
                vecAddXYZ(&center, (Vec4 *)(layout + 0x90), &offset);
            }
            switch (region->shape) {
            case 0x27:
                DEBUG_disp_region_object(0, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            case 0x28:
                DEBUG_disp_region_object(3, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            case 0x29:
                DEBUG_disp_region_object(2, *(void **)(layout + 0x134), rot, &color, mode, 2.0f, center.v[0], center.v[1]);
                break;
            case 0x2A:
                DEBUG_disp_region_object(1, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            }
        }
        if (count > 0) {
            glDrawNull(0.3f, *(void **)(layout + 0x134), (Vec4 *)colors[2], mode);
            glDrawLineArrow(*(void **)(layout + 0x134), &dir, (Vec4 *)colors[2], mode, 1.0f, 0.5f);
        }
    }
}
