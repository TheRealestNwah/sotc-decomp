typedef int s128 __attribute__((mode(TI)));
/* ~140 diffs, 168 vs 170 words. Arrow-water ripple effect update over a 25-entry table B_0018AD70 (stride 0x14: on, prev, pad, t, handle): spawns new entries (on && !prev) via func_00054388, round-robins one new handle via func_00054598 from the cursor at work+0x150, steps live ones (func_00052A38, func_000540D0), runs the group list (func_00052D18, stride 0x40), func_00053AE0, then copies on->prev and advances t by gcGlobalVar+0x190. Original builds the spawn predicate with two branches (v1 = 0 / 1 in delay slots) and keeps the table pointer in s0 with the work pointer in s1; ours uses sltiu and the opposite saved registers. */
typedef struct {
    int on;
    int prev;
    int pad8;
    float t;
    int handle;
} ArrowWater;

extern ArrowWater B_0018AD70[25];
extern char gcGlobalVar[];
extern int *getSpecialEffectObjWork(void *);
extern char *getEditWorkInitData(int);
extern void func_00053058(void *, void *, void *);
extern void func_00052A38(void *);
extern void func_000540D0(void *, int);
extern void func_00052D18(void *, void *);
extern void func_00053AE0(void *, void *, void *, void *, void *);

extern int B_0018AD78[];
extern char *GetLayoutClass(int);
extern float iosGetRandom(void);
extern int GetWaterSurfacePositionY(float *, float *, void *, float, float);

static inline void quatRotateVector(float *out, float *quat, float *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void addXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float randSign(float r)
{
    return (iosGetRandom() - 0.5f < 0.0f) ? -r : r;
}

typedef union { char *c; float f; } PU;
typedef union { char *c; int i; float f; } PI;
typedef struct { float x; int y; float z; int w; } __attribute__((aligned(8))) Ofs;
extern float ZUnitVector[];
extern float iosGetATan2fExact(float, float);
extern void func_00052558(void *);

static inline void setUnit(void *p)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(p) : "memory");
}

/* 13 diffs. Places a new ripple: unit vectors at +0x50/+0x60, flags reset, offset (layout 0x70/0x74 of the owner's +0x114 data) rotated by the layout quaternion and added to its position, facing from ZUnitVector, angle via iosGetATan2fExact, then func_00052558. Remaining diffs: the Original schedules the Ofs zero stores and the second quaternion load differently. */
#ifdef NONMATCHING
static void func_00054388(char *p, int i)
{
    float dir[4] __attribute__((aligned(16)));
    Ofs ofs __attribute__((aligned(16)));
    char *lay = GetLayoutClass(B_0018AD78[i * 5]);
    char *q;
    char *w;
    Ofs t;

    setUnit(p + 0x50);
    q = p + 0x60;
    setUnit(q);
    *(int *)(q + 0x10) = 0;
    *(int *)(q + 0x14) = 0;
    *(int *)(q + 0x18) = 1;
    *(int *)(p + 0x8) = 0;
    *(float *)(p + 0x10) = 1.0f;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x18) = 0;
    w = ((PI *)p)->c;
    t.x = *(float *)(((PU *)(w + 0x114))->c + 0x70);
    t.y = 0;
    t.z = *(float *)(((PU *)(w + 0x114))->c + 0x74);
    t.w = 0;
    ofs = t;
    quatRotateVector((float *)&ofs, (float *)*(int *)(lay + 0x13C), (float *)&ofs);
    addXYZ((float *)(p + 0x40), *(float **)(lay + 0x134), (float *)&ofs);
    *(s128 *)(p + 0x20) = *(s128 *)(p + 0x40);
    quatRotateVector(dir, (float *)*(int *)(lay + 0x13C), ZUnitVector);
    *(float *)(p + 0x34) = -dir[0];
    *(int *)(p + 0x38) = 0;
    *(float *)(p + 0x30) = dir[2];
    *(int *)(p + 0x3C) = 0;
    *(int *)(p + 0x18) = 0;
    *(float *)(p + 0x1C) = iosGetATan2fExact(-dir[0], dir[2]);
    func_00052558(p);
}
#endif

static int func_00054598(char *p, int i)
{
    float pos[4] __attribute__((aligned(16)));
    float ofs[4] __attribute__((aligned(16)));
    float out[4] __attribute__((aligned(16)));
    char *lay;
    float y;
    float d;

    lay = GetLayoutClass(B_0018AD78[i * 5]);
    if (lay == 0)
        return 0;
    ofs[0] = randSign(*(float *)(*(char **)(*(char **)p + 0x114) + 0x70));
    *(int *)&ofs[1] = 0;
    ofs[2] = randSign(*(float *)(((PU *)(*(char **)p + 0x114))->c + 0x74));
    *(int *)&ofs[3] = 0;
    quatRotateVector(ofs, *(float **)(lay + 0x13C), ofs);
    addXYZ(pos, (float *)(p + 0x20), ofs);
    d = 0.1f;
    y = *(float *)(p + 0x24);
    return GetWaterSurfacePositionY(out, pos, gcGlobalVar + 0x230, y + d, y - d);
}

static inline int pending(ArrowWater *e)
{
    if (e->on == 0)
        return 0;
    if (e->prev == 0)
        return 1;
    return 0;
}

#ifdef NONMATCHING
void arrowWaterMain(char *obj)
{
    int i;
    int n;
    int *w = getSpecialEffectObjWork(obj);
    int *s2 = (int *)w[0];
    char *fp = (char *)w[2];
    char *s6 = (char *)w[1];
    char *d = getEditWorkInitData(*(int *)(*(char **)(obj + 0x1C) + 8));
    char *s5 = fp;
    ArrowWater *e;
    char *s1;
    int s0;

    i = 0;
    n = s2[0xF4 / 4];
    s2[0x118 / 4] = 0;
    s2[0x11C / 4] = 0;
    if (n > 0) {
        s1 = s6;
        e = B_0018AD70;
        do {
            if (pending(e)) {
                func_00054388(s1, i);
                n = s2[0xF4 / 4];
            }
            i++;
            s1 += 0x80;
            e++;
        } while (i < n);
    }
    func_00053058(obj, s2, s6);
    *(float *)((char *)s2 + 0xFC) = *(float *)(d + 0x10);
    n = s2[0xF4 / 4];
    s0 = s2[0x150 / 4];
    *(float *)((char *)s2 + 0x100) = *(float *)(d + 0x14);
    *(float *)((char *)s2 + 0x104) = *(float *)(d + 0x18);
    *(float *)((char *)s2 + 0x108) = *(float *)(d + 0x1C);
    *(float *)((char *)s2 + 0x10C) = *(float *)(d + 0x20);
    *(float *)((char *)s2 + 0x110) = *(float *)(d + 0x24);
    for (i = 0; i < n; i++, s0++) {
        if (!(s0 < n))
            s0 = 0;
        if (B_0018AD70[s0].on != 0 && B_0018AD70[s0].handle == 0) {
            B_0018AD70[s0].handle = func_00054598(s6 + (s0 << 7), s0);
            s2[0x150 / 4] = s0 + 1;
            break;
        }
    }
    n = s2[0xF4 / 4];
    s1 = s6;
    e = B_0018AD70;
    for (i = 0; i < n; i++, s1 += 0x80, e++) {
        if (e->on != 0) {
            func_00052A38(s1);
            func_000540D0(s1, i);
            s2[0x118 / 4]++;
            n = s2[0xF4 / 4];
        }
    }
    for (i = 0; i < s2[0x120 / 4]; i++, s5 += 0x40)
        func_00052D18(s2 + 0x120 / 4, s5);
    func_00053AE0(obj, s2, s6, d, fp);
    for (e = B_0018AD70, i = 24; i >= 0; i--, e++) {
        e->prev = e->on;
        if (e->on != 0)
            e->t = e->t + *(float *)(gcGlobalVar + 0x190);
    }
}
#endif
