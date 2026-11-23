typedef int u_long128 __attribute__((mode(TI)));

typedef struct SkinInfo {
    char pad0[0x14];
    int unk14;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    int unk28;
    char pad2C[0x4];
    float unk30;
    float unk34;
} SkinInfo;

typedef struct ClipVisual {
    char pad0[0x8];
    SkinInfo *unk8;
    int unkC;
    char pad10[0x8];
    union {
        struct {
            int unk18;
            unsigned int unk1C;
        } w;
        long l;
    } u18;
    u_long128 unk20;
    char *unk30[1];
} ClipVisual;

typedef struct ClipCamera {
    char pad0[0x140];
    u_long128 unk140;
    char pad150[0x450];
    u_long128 unk5A0[4];
} ClipCamera;

typedef struct ClipObj {
    struct { char pad0[0x20]; ClipVisual *unk20; } *unk0;
    char pad4[0x22C];
    float unk230;
    float unk234;
    float unk238;
    char pad23C[0x14];
    union {
        float f;
        struct {
            long pad : 40;
            long clip : 3;
        } b;
    } unk250;
} ClipObj;

typedef union Vec4 {
    u_long128 q;
    struct { float x, y, z, w; } v;
} Vec4;

extern int D_001360C4;
extern ClipCamera *iosgluGetCameraContext(void);
extern float func_0001E9C0(void *, ClipObj *, void *, void *, ClipCamera *);
extern int clipByMinMaxCube(void *, void *, void *);
extern float func_0001CCF8(ClipVisual *, ClipObj *, void *, float);

static inline float dist(void *a, void *b) {
    float r;
    __asm__ volatile(
        "lqc2 vf5, 0(%1)\n\t"
        "lqc2 vf6, 0(%2)\n\t"
        "vsub.xyzw vf7, vf5, vf6\n\t"
        "vmul.xyz vf7, vf7, vf7\n\t"
        "vmulax.w ACC, vf0, vf7x\n\t"
        "vmadday.w ACC, vf0, vf7y\n\t"
        "vmaddz.w vf7, vf0, vf7z\n\t"
        ".word 0x4BA703BD\n\t"
        "vwaitq\n\t"
        "cfc2 $2, $vi22\n\t"
        "mtc1 $2, %0"
        : "=f"(r)
        : "r"(a), "r"(b)
        : "$2");
    return r;
}


float modelClipSolid(ClipObj *obj, char *arg1) {
    Vec4 pos;
    Vec4 sph;
    Vec4 tmp;
    Vec4 mat[4];
    Vec4 *p;
    ClipCamera *cam;
    ClipVisual *vis;
    SkinInfo *info;
    float d;
    float f;
    float h;
    float lod;
    float r;
    float cur;
    float res;

    cam = iosgluGetCameraContext();
    vis = obj->unk0->unk20;
    if (!((int)((vis->u18.l << 8) >> 32) & 1)) {
        if (D_001360C4 != 0 && 0.0f < (f = vis->unk8->unk30) && dist(arg1 + 0x30, &cam->unk140) < f) {
            return -2.0f;
        }
    } else {
        return -2.0f;
    }
    sph.q = vis->unk20;
    sph.v.w = sph.v.w * obj->unk250.f;
    r = func_0001E9C0(&pos, obj, &sph, arg1, cam);
    info = vis->unk8;
    p = &pos;
    switch (info->unk14) {
    case 0:
        d = obj->unk234;
        break;
    case 1:
        d = obj->unk238;
        break;
    case 2:
        d = obj->unk230;
        break;
    case 3:
        tmp.q = iosgluGetCameraContext()->unk140;
        p->v.y = 0.0f;
        tmp.v.y = 0.0f;
        d = dist(p, &tmp);
        info = vis->unk8;
        break;
    case 4:
        d = dist(p, &iosgluGetCameraContext()->unk140);
        info = vis->unk8;
        break;
    default:
        d = 0.0f;
        break;
    }
    if (info->unk20 < d) {
        lod = 3.0f;
    } else if (info->unk1C < d) {
        lod = 2.0f;
    } else if (info->unk18 < d) {
        lod = 1.0f;
    } else {
        lod = 0.0f;
    }
    h = info->unk24;
    if (0.0f < h && 0.0f <= lod) {
        cur = (float)(int)obj->unk250.b.clip;
        if (cur < lod) {
            if (vis->unk8->unk20 + h < d) {
                lod = 3.0f;
            } else if (vis->unk8->unk1C + h < d) {
                lod = 2.0f;
            } else if (vis->unk8->unk18 + h < d) {
                lod = 1.0f;
            }
        } else if (lod < cur) {
            if (d < vis->unk8->unk18 - h) {
                lod = 0.0f;
            } else if (d < vis->unk8->unk1C - h) {
                lod = 1.0f;
            } else if (d < vis->unk8->unk20 - h) {
                lod = 2.0f;
            }
        }
    }
    if (!((unsigned int)(int)lod < vis->u18.w.unk1C)) {
        if (info->unk28 != 0) {
            res = -1.0f;
            goto check;
        }
        lod = (float)(vis->u18.w.unk1C - 1);
    }
    if (vis->unkC != 0) {
        lod = func_0001CCF8(vis, obj, arg1, lod);
    }
    res = lod;
check:
    if (res < 0.0f) {
        return -1.0f;
    }
    if (0.0f <= r && vis->unk30 != 0) {
        char *box = vis->unk30[(int)res];
        __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n\t"
                             "lqc2 vf15, 0x10(%1)\n\t"
                             "lqc2 vf16, 0x20(%1)\n\t"
                             "lqc2 vf17, 0x30(%1)\n\t"
                             "lqc2 vf24, 0x0(%2)\n\t"
                             "lqc2 vf25, 0x10(%2)\n\t"
                             "lqc2 vf26, 0x20(%2)\n\t"
                             "lqc2 vf27, 0x30(%2)\n\t"
                             "vmulax.xyzw ACC, vf14, vf24x\n\t"
                             "vmadday.xyzw ACC, vf15, vf24y\n\t"
                             "vmaddaz.xyzw ACC, vf16, vf24z\n\t"
                             "vmaddw.xyzw vf24, vf17, vf24w\n\t"
                             "vmulax.xyzw ACC, vf14, vf25x\n\t"
                             "vmadday.xyzw ACC, vf15, vf25y\n\t"
                             "vmaddaz.xyzw ACC, vf16, vf25z\n\t"
                             "vmaddw.xyzw vf25, vf17, vf25w\n\t"
                             "vmulax.xyzw ACC, vf14, vf26x\n\t"
                             "vmadday.xyzw ACC, vf15, vf26y\n\t"
                             "vmaddaz.xyzw ACC, vf16, vf26z\n\t"
                             "vmaddw.xyzw vf26, vf17, vf26w\n\t"
                             "vmulax.xyzw ACC, vf14, vf27x\n\t"
                             "vmadday.xyzw ACC, vf15, vf27y\n\t"
                             "vmaddaz.xyzw ACC, vf16, vf27z\n\t"
                             "vmaddw.xyzw vf27, vf17, vf27w\n\t"
                             "sqc2 vf24, 0x0(%0)\n\t"
                             "sqc2 vf25, 0x10(%0)\n\t"
                             "sqc2 vf26, 0x20(%0)\n\t"
                             "sqc2 vf27, 0x30(%0)"
                             : : "r"(mat), "r"(cam->unk5A0), "r"(arg1) : "memory");
        if (clipByMinMaxCube(box, box + 0x10, mat) != 0) {
            return -2.0f;
        }
    }
    return res;
}
