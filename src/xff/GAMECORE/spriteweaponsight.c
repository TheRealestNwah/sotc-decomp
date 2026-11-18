/* The sight parts are written through a union member: gcc 2.96 gives union
   member accesses alias set 0, so every store reloads spr->parts like the
   Original (which behaves as if built without strict aliasing). */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int i[4]; } IVec4;
typedef struct { int pad0; int *run; int pad8[2]; } SpriteParam;

typedef union { struct { char pad[8]; float v; } s; } SightPart;
typedef struct {
    SightPart **parts;
    char pad4[8];
    float x;
    float y;
    char pad14[8];
    int z;
    char pad20[0x10];
    float alpha;
    char pad34[0x20];
    void (*draw)(void *);
} SightSprite;

extern int D_0017B330;
extern Vec4 D_0017B340;
extern Vec4 D_0017B350;
extern int D_0017B360;
extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern SightSprite *GetSpriteClass(void *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern char *iosgluGetCameraContext(void);
extern void iosFTOI0Vector(IVec4 *, Vec4 *);
extern void scrRun(void);

static inline void applyMatrix(Vec4 *out, void *m, Vec4 *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void scaleVector(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

void spriteweaponsight(SpriteParam *param)
{
    SpriteParam p;
    Vec4 v;
    Vec4 w;
    IVec4 iv;
    void *thread;
    SightSprite *spr;

    thread = isysGetThisSubThread();
    spr = GetSpriteClass(thread);
    ScrSpriteParamSetup(&p, param);
    while (*p.run != 0) {
        if (D_0017B360 != 0) {
            applyMatrix(&v, iosgluGetCameraContext() + 0x660, &D_0017B340);
            if (0.0f < v.f[3]) {
                scaleVector(&v, &v, 1.0f / v.f[3]);
                v.f[0] -= 2048.0f;
                v.f[1] -= 2048.0f;
                switch (D_0017B330) {
                case 1:
                case 2:
                case 3:
                    spr->parts[0]->s.v = 1.0f;
                    spr->parts[1]->s.v = 0.0f;
                    spr->parts[2]->s.v = 0.0f;
                    break;
                case 4:
                case 6:
                case 7:
                    spr->parts[0]->s.v = 0.0f;
                    spr->parts[1]->s.v = 1.0f;
                    spr->parts[2]->s.v = 0.0f;
                    break;
                case 5:
                    spr->parts[0]->s.v = 0.0f;
                    spr->parts[1]->s.v = 0.0f;
                    spr->parts[2]->s.v = 1.0f;
                    break;
                default:
                    spr->parts[0]->s.v = 0.0f;
                    spr->parts[1]->s.v = 0.0f;
                    spr->parts[2]->s.v = 0.0f;
                    break;
                }
                spr->alpha = 1.0f;
                spr->x = v.f[0];
                spr->y = v.f[1];
                iosFTOI0Vector(&iv, &v);
                applyMatrix(&w, iosgluGetCameraContext() + 0x1A0, &D_0017B350);
                w.f[2] += 0.3f;
                applyMatrix(&w, iosgluGetCameraContext() + 0x4A0, &w);
                scaleVector(&w, &w, 1.0f / w.f[3]);
                iosFTOI0Vector(&iv, &w);
                spr->z = iv.i[2];
                if (*(int *)(gcGlobalVar + 0x1AC) == 0)
                    spr->draw(thread);
            }
        } else {
            spr->alpha = 0;
        }
        scrRun();
    }
}
