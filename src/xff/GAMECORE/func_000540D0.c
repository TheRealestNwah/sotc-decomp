/* Parked: 158 diffs, same size (incl. the split tail func_00054350). Per-slot layout sync for a 25-entry table (B_0018AD70, 0x14 bytes each, object id at +8, active flag at +0x10): if the object's layout class exists and the slot is active, builds a yaw quaternion from o+0x30/o+0x34 (sign-flipped for negative o+0x34), stores it in the layout, rotates the owner-derived offset vector by it (VU0 quaternion-to-matrix block applied straight from registers), writes layout position = o+0x20 - rotated offset, regenerates the layout matrix at +0x158 and calls UpdateLayoutClassGeometry; if the layout is gone, clears and re-arms the slot found by id. Remaining: not diffed in detail yet. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern char B_0018AD70[];
extern char *GetLayoutClass(int);
extern void *memset(void *, int, unsigned int);
extern void UpdateLayoutClassPastGeometry(char *);
extern void UpdateLayoutClassGeometry(char *);
extern void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *, void *, float);

#define QUAT_MATRIX                                             \
    "vaddw.xyz vf12, vf0, vf0w\n"                               \
    "lqc2 vf11, 0x0(%1)\n"                                      \
    "vmr32.w vf14, vf0\n"                                       \
    "vmr32.w vf15, vf0\n"                                       \
    "vmr32.w vf16, vf0\n"                                       \
    "vopmula.xyz ACC, vf11, vf12\n"                             \
    "vmadd.xyz vf11, vf0, vf0\n"                                \
    "vmadd.xyz vf10, vf11, vf12\n"                              \
    "vmul.xyz vf13, vf11, vf10\n"                               \
    "vopmula.xyz ACC, vf11, vf10\n"                             \
    "vmaddw.xyz vf15, vf10, vf11w\n"                            \
    "vmsubw.xyz vf16, vf10, vf11w\n"                            \
    "vopmula.xyz ACC, vf13, vf12\n"                             \
    "vmadd.xyz vf17, vf13, vf12\n"                              \
    "vopmula.xyz ACC, vf15, vf12\n"                             \
    "vmadd.xyz vf15, vf0, vf0\n"                                \
    "vsub.xyz vf14, vf12, vf17\n"                               \
    "vmove.yz vf17, vf14\n"                                     \
    "vmove.y vf14, vf16\n"                                      \
    "vmove.y vf16, vf15\n"                                      \
    "vmove.y vf15, vf17\n"                                      \
    "vmove.z vf14, vf15\n"                                      \
    "vmove.z vf15, vf16\n"                                      \
    "vmove.z vf16, vf17\n"

static void func_000540D0(char *o, int idx)
{
    struct {
        float axis[4];
        s128 q;
        s128 v;
        float t[4];
    } L __attribute__((aligned(16)));
    char *ent;
    char *lay;
    char *e;
    int i;
    int id;
    float zero;
    float y;

    ent = B_0018AD70 + idx * 0x14;
    id = *(int *)(ent + 8);
    lay = GetLayoutClass(id);
    if (lay != 0) {
        char *c = B_0018AD70 + idx * 0x14;

        if (*(int *)(c + 0x10) == 0)
            return;
        memset(L.axis, 0, 0x10);
        zero = 0.0f;
        L.axis[1] = 1.0f;
        UpdateLayoutClassPastGeometry(lay);
        y = L.axis[1];
        if (*(float *)(o + 0x34) < zero)
            y = -y;
        L.axis[1] = y;
        SetQuaternionByCosineAxisRotateVWithNoRegularize(&L.q, L.axis, *(float *)(o + 0x30));
        **(s128 **)(lay + 0x13C) = L.q;
        {
            char *o114 = *(char **)(*(char **)o + 0x114);

            L.t[0] = *(float *)(o114 + 0x70);
            L.t[1] = zero;
            L.t[2] = *(float *)(o114 + 0x74);
            L.t[3] = zero;
            L.v = *(s128 *)L.t;
        }
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n" QUAT_MATRIX
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf0, vf8w\n"
                             "sqc2 vf10, 0x0(%0)\n"
                             :
                             : "r"(&L.v), "r"(*(char **)(lay + 0x13C))
                             : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(o + 0x20), "r"(&L.v), "r"(*(char **)(lay + 0x134))
                             : "memory");
        __asm__ __volatile__(QUAT_MATRIX
                             "sqc2 vf14, 0x0(%2)\n"
                             "sqc2 vf15, 0x10(%2)\n"
                             "sqc2 vf16, 0x20(%2)\n"
                             "lqc2 vf4, 0x0(%3)\n"
                             "vmove.w vf4, vf0\n"
                             "sqc2 vf4, 0x30(%2)\n"
                             :
                             : "r"(0), "r"(*(char **)(lay + 0x13C)), "r"(*(char **)(lay + 0x158)), "r"(*(char **)(lay + 0x134))
                             : "memory");
        UpdateLayoutClassGeometry(lay);
        return;
    }
    e = B_0018AD70 + 8;
    for (i = 0; i < 0x19; i++) {
        if (*(int *)(e + i * 0x14) == id) {
            *(int *)(B_0018AD70 + i * 0x14) = 0;
            *(int *)(e + i * 0x14) = 0;
            *(int *)(B_0018AD70 + i * 0x14 + 0xC) = 0;
            *(int *)(B_0018AD70 + i * 0x14 + 0x10) = 1;
            break;
        }
    }
}
#endif
