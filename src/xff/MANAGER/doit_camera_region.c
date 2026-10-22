typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float v[4];
} __attribute__((aligned(16))) Vec4;

typedef struct {
    int unk0;
    int unk4;
    long unk8;
    void *unk10;
    int unk14;
    int pad18[2];
    Vec4 unk20;
} CameraRegion;

#define VU_QUAT_MUL(dst, a, b) \
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n" \
                         "lqc2 vf12, 0x0(%1)\n" \
                         "vmul.xyzw vf13, vf11, vf12\n" \
                         "vaddy.x vf13, vf13, vf13y\n" \
                         "vaddz.x vf13, vf13, vf13z\n" \
                         "vsubx.w vf13, vf13, vf13x\n" \
                         "vmulw.xyz vf14, vf12, vf11w\n" \
                         "vmulw.xyz vf15, vf11, vf12w\n" \
                         "vopmula.xyz ACC, vf12, vf11\n" \
                         "vopmsub.xyz vf16, vf11, vf12\n" \
                         "vadd.xyz vf13, vf14, vf15\n" \
                         "vadd.xyz vf13, vf13, vf16\n" \
                         "sqc2 vf13, 0x0(%2)\n" \
                         : : "r"(a), "r"(b), "r"(dst) : "memory")

extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void DivQuaternion(Vec4 *, Vec4 *, Vec4 *);
extern int is_parent_obj_boss_camera_region(CameraRegion *);

void doit_camera_region(CameraRegion *r, void *obj)
{
    char *layout = GetLayoutClass(r->unk10);
    *(s128 *)&r->unk20 = **(s128 **)(layout + 0x13C);
    if (obj != 0 && is_parent_obj_boss_camera_region(r) == 1) {
        char *parent = GetLayoutClass(obj);
        *(int *)(layout + 0x1AC) = *(int *)(parent + 0x1AC);
        if (*(int *)((char *)r->unk14 + 8) == 2) {
            Vec4 q;
            DivQuaternion(&q, &r->unk20, *(Vec4 **)(parent + 0x13C));
            VU_QUAT_MUL(&r->unk20, GetCharacterClass(obj) + 0x470, &q);
        }
    }
}
