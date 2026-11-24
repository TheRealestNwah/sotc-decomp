/* LOD factor for a clip visual by its distance mode. Called from modelClipSolid and modelClipSkin. */
typedef int u_long128 __attribute__((mode(TI)));

typedef union Vec4 {
    u_long128 q;
    struct { float x, y, z, w; } v;
} Vec4;

typedef struct ClipVisual {
    char pad0[0xC];
    float *unkC;
    char pad10[0x8];
    long unk18;
    u_long128 unk20;
} ClipVisual;

typedef struct ClipCamera {
    char pad0[0x140];
    float pos[4];
    float dir[4];
} ClipCamera;

typedef struct ClipObj {
    char pad0[0x234];
    float unk234;
    char pad238[0x10];
    float unk248;
} ClipObj;

extern void iosCopyMatrix(void *, void *);
extern void iosApplyRotMatrix(void *, void *, void *);
extern ClipCamera *iosgluGetCameraContext(void);
extern void *memset(void *, int, unsigned int);

static inline void applyMatrix(Vec4 *o, float *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(o), "r"(m), "r"(v) : "memory");
}

static inline void subXYZ(Vec4 *out, Vec4 *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float length(Vec4 *a)
{
    float r;
    float lodf;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline float dist(Vec4 *a, float *b)
{
    float r;
    float lodf;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline float dot3(Vec4 *a, float *b)
{
    float r;
    float lodf;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static float func_0001CCF8(ClipVisual *vis, ClipObj *obj, void *mtx, float lod)
{
    float m[16];
    Vec4 pos;
    Vec4 dir;
    float *t;
    float d;
    float r;
    float lodf;

    t = (float *)vis->unkC;
    d = -1.0f;
    iosCopyMatrix(m, mtx);
    switch ((int)((vis->unk18 << 29) >> 32) & 7) {
    case 0:
        return lod;
    case 1:
        d = obj->unk234;
        break;
    case 2:
        pos.q = vis->unk20;
        pos.v.w = 1.0f;
        applyMatrix(&pos, m, &pos);
        subXYZ(&pos, &pos, iosgluGetCameraContext()->pos);
        pos.v.y = 0.0f;
        d = length(&pos);
        break;
    case 3:
        pos.q = vis->unk20;
        pos.v.w = 1.0f;
        applyMatrix(&pos, m, &pos);
        d = dist(&pos, iosgluGetCameraContext()->pos);
        break;
    case 4:
        pos.q = vis->unk20;
        pos.v.w = 1.0f;
        applyMatrix(&pos, m, &pos);
        if (pos.v.x - iosgluGetCameraContext()->pos[0] < 0.0f)
            d = -(pos.v.x - iosgluGetCameraContext()->pos[0]);
        else
            d = pos.v.x - iosgluGetCameraContext()->pos[0];
        break;
    case 5:
        pos.q = vis->unk20;
        pos.v.w = 1.0f;
        applyMatrix(&pos, m, &pos);
        if (pos.v.y - iosgluGetCameraContext()->pos[1] < 0.0f)
            d = -(pos.v.y - iosgluGetCameraContext()->pos[1]);
        else
            d = pos.v.y - iosgluGetCameraContext()->pos[1];
        break;
    case 6:
        pos.q = vis->unk20;
        pos.v.w = 1.0f;
        applyMatrix(&pos, m, &pos);
        if (pos.v.z - iosgluGetCameraContext()->pos[2] < 0.0f)
            d = -(pos.v.z - iosgluGetCameraContext()->pos[2]);
        else
            d = pos.v.z - iosgluGetCameraContext()->pos[2];
        break;
    }
    /* Keeps gcc from stealing the next dsll into a beql likely slot on the
       switch range check; the Original fills the slot from the jump table. */
    __asm__ __volatile__("");
    if ((int)((vis->unk18 << 26) >> 32) & 1) {
        memset(&dir, 0, 16);
        dir.v.z = -1.0f;
        iosApplyRotMatrix(&dir, mtx, &dir);
        if (dot3(&dir, iosgluGetCameraContext()->dir) < 0.0f)
            return -3.0f;
    }
    if (d < t[0])
        r = t[1];
    else if (d < t[2])
        r = t[1] + (t[3] - t[1]) * (d - t[0]) / (t[2] - t[0]);
    else if (d < t[4])
        r = t[3] + (t[5] - t[3]) * (d - t[2]) / (t[4] - t[2]);
    else if (d < t[6])
        r = t[5] + (t[7] - t[5]) * (d - t[4]) / (t[6] - t[4]);
    else
        r = t[7];
    lodf = 1.0f - r;
    obj->unk248 = lodf;
    if (lodf == 1.0f)
        return -3.0f;
    return lod;
}
