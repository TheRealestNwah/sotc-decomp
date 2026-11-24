/* Random ground point around a layout position: picks a random angle and radius in [min, max], rotates the XZ offset by the quaternion from YUnitVector to dir, then casts a ray of +/-len along dir through ClipCollisionDirectCallBack and copies the 64-byte hit to out. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { long long w[8]; } Hit;

extern char YUnitVector[];
extern char XUnitVector[];
extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);
extern float iosGetRandom(void);
extern float iosGetTableCos(short);
extern float iosGetTableSin(short);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, void *, int);
extern int AI_JudgeNotCharaObjFunc();
extern int AI_JudgeColAttrFunc();

static inline Vec4 *quatRotate(Vec4 *vec0, Vec4 *quat)
{
    register Vec4 *vec __asm__("$2") = vec0;
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
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(vec), "r"(quat) : "memory");
}

static inline void vadd(Vec4 *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vscale(Vec4 *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

Hit *AI_GetGeometryPointerOfLayout(Hit *out, Vec4 *pos, Vec4 *dir, float min, float max, float len)
{
    struct {
        Vec4 a;
        Vec4 b;
        Vec4 t2;
        Vec4 t1;
        Hit hit;
        Vec4 pad;
        Vec4 q;
        Vec4 v;
    } L __attribute__((aligned(16)));
    float ang;
    float r;
    short s;
    Vec4 *a;

    isysGetThisSubThread();
    max -= min;
    GetDifferencialQuaternionWithNoRegularize(&L.q, dir, YUnitVector, XUnitVector);
    ang = iosGetRandom() * 2.0f * 3.1415925026f;
    r = min + max * iosGetRandom();
    s = (int)(ang * 32768.0f / 3.1415925026f);
    L.v.f[0] = iosGetTableSin(s) * r;
    L.v.f[1] = 0.0f;
    L.v.f[2] = iosGetTableCos(s) * r;
    L.v.f[3] = 0.0f;
    quatRotate(&L.v, &L.q);
    vadd(&L.a, pos, &L.v);
    L.b.q = L.a.q;
    vscale(&L.t1, dir, len);
    a = &L.a;
    vscale(&L.t2, dir, -len);
    vadd(a, a, &L.t2);
    vadd(&L.b, &L.b, &L.t1);
    if (ClipCollisionDirectCallBack(&L.hit, a, &L.b, gcGlobalVar + 0x230, AI_JudgeNotCharaObjFunc, 0, 0, AI_JudgeColAttrFunc, 0) == 0)
        return 0;
    *out = L.hit;
    return out;
}
