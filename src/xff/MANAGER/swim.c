typedef int s128 __attribute__((mode(TI)));
typedef struct {
    s128 q0;
    s128 q10;
    s128 q20;
    s128 q30;
    s128 q40;
    char pad50[0x30];
    int x80;
    int pad84[3];
} SlideResult;
extern s128 ZeroPoint;
extern s128 ZeroVector;
extern char *GetCharacterClass(int);
extern void charrootdyn_updateCharacterClassParentGeometry(char *, s128 *, char *);
extern void StabilizeToYRotQuaternion(void *);
extern int charrootdyn_addWindDynamicsToRoot(char *, float, float);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern void charrootdyn_getCollisionDB(void *, void *, int, void *, void *, int, float);
extern int charrootdyn_getWaterStatus(char *, void *, void *, void *, void *, float);
extern int charrootdyn_HslidecollisionCB(void *, void *, void *, void *, void *, void *, int, int, int, float, float);
extern void charrootdyn_setkeepcolhitstatus(char *, void *, void *, void *, void *, float);
extern void charrootdyn_restoreposition(void *, int, void *, void *, void *, int);
extern int charrootdyn_getLandingSurface(void *, void *, void *, void *, float);
extern void charrootdyn_setHColFindStatus(char *, void *, float);
extern void charrootdyn_getChainStatus(int);
extern void charrootdyn_getvelocity(void *, void *, void *, float);
extern void GetCharaVCollisionStatus(char *);
#define rotatePointR(o, p, q, S) do { register void *_o asm("a0") = (o); register void *_p asm("v0") = (p); S; __asm__ __volatile__("lqc2 vf08, 0x0(%1)\n" "vaddw.xyz vf12, vf00, vf00w\n" "lqc2 vf11, 0x0(%2)\n" "vmr32.w vf14, vf00\n" "vmr32.w vf15, vf00\n" "vmr32.w vf16, vf00\n" "vopmula.xyz ACC, vf11, vf12\n" "vmadd.xyz vf11, vf00, vf00\n" "vmadd.xyz vf10, vf11, vf12\n" "vmul.xyz vf13, vf11, vf10\n" "vopmula.xyz ACC, vf11, vf10\n" "vmaddw.xyz vf15, vf10, vf11w\n" "vmsubw.xyz vf16, vf10, vf11w\n" "vopmula.xyz ACC, vf13, vf12\n" "vmadd.xyz vf17, vf13, vf12\n" "vopmula.xyz ACC, vf15, vf12\n" "vmadd.xyz vf15, vf00, vf00\n" "vsub.xyz vf14, vf12, vf17\n" "vmove.yz vf17, vf14\n" "vmove.y vf14, vf16\n" "vmove.y vf16, vf15\n" "vmove.y vf15, vf17\n" "vmove.z vf14, vf15\n" "vmove.z vf15, vf16\n" "vmove.z vf16, vf17\n" "vmulax.xyzw ACC, vf14, vf08x\n" "vmadday.xyzw ACC, vf15, vf08y\n" "vmaddaz.xyzw ACC, vf16, vf08z\n" "vmaddw.xyzw vf10, vf00, vf08w\n" "sqc2 vf10, 0x0(%0)\n" : : "r"(_o), "r"(_p), "r"(q)); } while (0)
#define NEARZERO(x) ((x) < 0.0f ? -0.01f < (x) : (x) < 0.01f)
extern void ForceUnparentLayoutObj(void *);
extern long *GetCollisionDBAttributeAdr(void *);

static int func_0006BE30(void *collision);

static inline void rotatePoint(void *out, void *point, void *quaternion)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf00, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(point), "r"(quaternion));
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void subXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZW(void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

void swim(int id, s128 *last, s128 *vel, int vcol, float unused, float dt, float vt, int wind)
{
    struct {
        s128 mv;
        float w[4];
        float d[4];
        s128 a;
        s128 b;
        s128 off;
        SlideResult r;
    } L;
    char *cls;
    s128 *pos;
    s128 *prev;
    s128 *quat;
    char *db;
    register char *finder asm("$20");
    int parent;
    float radius;
    float acc;
    float d;
    int windRes;
    int hit;
    int still;
    float k;
    s128 *q;
    s128 *po;

    cls = GetCharacterClass(id);
    pos = *(s128 **)(cls + 0x134);
    prev = *(s128 **)(cls + 0x138);
    quat = *(s128 **)(cls + 0x13C);
    k = 0x1.aaaaacp+2f;
    db = cls + 0xE20;
    finder = cls + 0x4C0;
    windRes = 0;
    parent = *(int *)(cls + 0x1C0);
    hit = 0;
    radius = *(float *)(cls + 0xE34);
    charrootdyn_updateCharacterClassParentGeometry(cls, &ZeroPoint, cls + 0x6D0);
    StabilizeToYRotQuaternion(*(void **)(cls + 0x13C));
    still = 0;
    q = quat;
    { register s128 t asm("v1") = *vel; /* The laundered operand keeps the velocity store based on cls, not on $v0. */
    rotatePointR(&L.mv, ({ char *pp = cls + 0x6F0; __asm__("" : "+r"(pp)); pp; }), q, *(s128 *)(cls + 0x6F0) = t); }
    scaleXYZW(&L.mv, dt);
    addXYZ(pos, pos, &L.mv);
    if (wind != 0)
        windRes = charrootdyn_addWindDynamicsToRoot(cls, *(float *)(cls + 0x3EC), dt);
    charrootdyn_getRegularColFinderPosition(finder, cls, q, pos);
    charrootdyn_getCollisionDB(db, *(char **)(cls + 0xE38) + *(short *)(cls + 0x370) * 4, id, finder, cls + 0x4D0, parent, radius);
    acc = 0.0f;
    if (charrootdyn_getWaterStatus(cls, L.w, *(char **)(cls + 0xE38) + *(short *)(cls + 0x370) * 4, db, pos, -*(float *)(cls + 0x3DC)) != 0) {
        subXYZ(L.d, pos, last);
        d = L.d[1] - L.w[1];
        if (acc < d) {
            if (1.5f < d) {
                acc = -14.699999f;
            } else {
                acc = d * -14.699999f * 0x1.555554p-1f;
                *(float *)(cls + 0xB30) *= 0.8f;
            }
        } else {
            if (d < -0.15f)
                acc = 10.0f;
            else
                acc = -d * 10.0f * k;
            *(float *)(cls + 0xB30) *= 0.8f;
        }
        if (NEARZERO(d) && NEARZERO(*(float *)(cls + 0xB30)))
            still = 1;
    } else {
        acc = -14.699999f;
    }
    *(float *)(cls + 0xB30) += acc * dt;
    ((float *)pos)[1] += *(float *)(cls + 0xB30) * dt;
    rotatePoint(&L.off, cls + 0xE00, quat);
    addXYZ(&L.a, prev, &L.off);
    addXYZ(&L.b, pos, &L.off);
    if (charrootdyn_HslidecollisionCB(&L.r, &L.a, &L.b, &ZeroVector, db, func_0006BE30, 0, 0, 0, *(float *)(cls + 0xE0C), 0.01f) != 0) {
        charrootdyn_setkeepcolhitstatus(cls, &L.r.q20, &L.r, &L.r.q30, &L.r.q40, *(float *)(cls + 0x3E4));
        subXYZ(prev, &L.r.q10, &L.off);
        subXYZ(pos, &L.r, &L.off);
        hit = 1;
    }
    charrootdyn_restoreposition(pos, id, quat, pos, last, !hit && (windRes ? 0 : still));
    if (charrootdyn_getLandingSurface(&L.r, db, prev, pos, -*(float *)(cls + 0x3DC)) != 0)
        charrootdyn_setHColFindStatus(cls, &L.r, 0.0f);
    charrootdyn_getChainStatus(id);
    charrootdyn_getvelocity(cls + 0x30, pos, prev, vt);
    if (vcol != 0)
        GetCharaVCollisionStatus(cls);
}

void motrootdyn_startswim(void *actor, char *m)
{
    ForceUnparentLayoutObj(actor);
    *(float *)(m + 0xB30) = *(float *)(m + 0x34) * 0.5f;
}

static int func_0006BE30(void *collision)
{
    long attr = *GetCollisionDBAttributeAdr(collision);

    if ((attr & 0x7C00) == 0x3C00) {
        return 0;
    }
    return (attr & 0x7C000000) != 0x14000000;
}
