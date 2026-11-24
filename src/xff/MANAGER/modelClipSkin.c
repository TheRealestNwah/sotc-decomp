/* Parked: 5 diffs (was 10), same size (252 words). Remaining: the prologue tests vis->unk8 with bnel in $v0,
 * where the Original loads it into $a0 and uses beqz with a "daddu $a1, $a0" delay slot, then reads unk30
 * through $a1. Permuter (-j2, 30 min) found nothing better on the 10-diff version. */
#ifdef NONMATCHING
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
} ClipVisual;

typedef struct ClipCamera {
    char pad0[0x140];
    u_long128 unk140;
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

float modelClipSkin(ClipObj *obj, char *arg1) {
    Vec4 pos;
    Vec4 sph;
    Vec4 tmp;
    Vec4 *p;
    ClipCamera *cam;
    ClipVisual *vis;
    SkinInfo *info;
    unsigned int n;
    float scale;
    float d;
    float f;
    float h;
    float lod;
    float r;
    float cur;

    cam = iosgluGetCameraContext();
    vis = obj->unk0->unk20;
    scale = 1.2f;
    if (vis->unk8 != 0) {
        scale = vis->unk8->unk34;
    }
    /* Copies vis->unk8 into its own register like the Original's delay-slot daddu. */
    {
        SkinInfo *ii = vis->unk8;
        __asm__ __volatile__("" : "+r"(ii));
        info = ii;
    }
    if (!((int)((vis->u18.l << 8) >> 32) & 1)) {
        if (D_001360C4 != 0 && 0.0f < (f = info->unk30) && dist(arg1 + 0x30, &cam->unk140) < f) {
            return -2.0f;
        }
    } else {
        return -2.0f;
    }
    sph.q = vis->unk20;
    sph.v.w = sph.v.w * (obj->unk250.f * scale);
    r = func_0001E9C0(&pos, obj, &sph, arg1, cam);
    if ((vis->u18.w.unk18 & 1) && sph.v.w <= r) {
        return -2.0f;
    }
    n = vis->u18.w.unk1C;
    if (n == 1) {
        return 0.0f;
    }
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
        n = vis->u18.w.unk1C;
        break;
    case 4:
        d = dist(p, &iosgluGetCameraContext()->unk140);
        info = vis->unk8;
        n = vis->u18.w.unk1C;
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
    if (!((unsigned int)(int)lod < n)) {
        if (info->unk28 != 0) {
            return -1.0f;
        }
        lod = (float)(n - 1);
    }
    if (vis->unkC != 0) {
        lod = func_0001CCF8(vis, obj, arg1, lod);
    }
    return lod;
}
#else
typedef struct ClipObj ClipObj;
extern float modelClipSkin(ClipObj *obj, char *arg1);
#endif
