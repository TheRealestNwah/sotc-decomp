/* Includes the split tail func_00092920. Shoulder edge fit: while the geometry pointer is an edge (type 4) and the root dynamics allow it, offsets the pointer position along the class quaternion axes and tries charrootdyn_detectCharClimbableWall; on a hit it clamps the hit parameter to [0, 1], otherwise it clips the edge parameter against the planes through both edge vertices, intersects the edge with the target plane and the class plane, and pushes the result off any collision found by ClipCollisionFinderCallBack. The object-space offset of B_0018B7C0 (x and w zeroed) is added and func_00091CE0 stores B_0018B800, setting B_0018B804. The detect call goes through a function type with the cc + 0xE20 argument last: EABI still passes it in $t1, and this order puts it in the jal delay slot like the Original. The hit clamp passes p through an opaque asm so w is reloaded through a1, and the zeroed x/w go through one float local, stored w first. */
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { Vec4 v; char pad[0x30]; Vec4 pos; char pad2[0x50]; } ColResult;
typedef struct { char pad[0x40]; Vec4 pos; } ColResult2;
typedef struct { float *p0; float *p1; } EdgePts;
typedef struct { char pad[0xC]; float t; int flag; char pad2[0x2C]; } GeoPtr;

extern int *DldSysUndefSymbol;
extern int MotRootDyn_EDGEXZ;
extern int MotRootDyn_EDGEPOINT;
extern char B_0018B7B0[], B_0018B7C0[], B_0018B7E0[], B_0018B7F0[];
extern int B_0018B804;
extern float B_0018B800;
extern char *GetCharacterClass(int);
extern void GetGeometryPointerPosition(void *, void *);
extern int GetGeometryPointerCollisionDB(void *);
extern int charrootdyn_detectCharClimbableWall(void *, int, int, void *, void *, void *, float, float, float, float);
extern void GetCollisionEdgePointerVertexPoint(void *, void *);
extern void CopyGeometryPointer(void *, void *);
extern void CompletePlaneD(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern void GetPlaneFittingPoint(void *, void *, void *);
extern int ClipCollisionFinderCallBack(void *, void *, void *, void *, void *, int);
extern void character_ikcolattrfilter();
static float func_00091CE0(void *, void *, char *, char *, char *, int);

static inline int dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline void axisZ(void *dst, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void axisY(void *dst, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void axisX(void *dst, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void scale(void *dst, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(s) : "memory");
}

static inline void add(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void sub(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float dot(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void normalize(void *dst, void *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

static inline void matVec(void *dst, void *m, void *v)
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
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}

static inline void intersect(void *out, void *plane, float *p0, float *p1, Vec4 *d)
{
    float t;

    sub(d, p1, p0);
    t = dot(plane, d);
    if (t < 0.0f ? t < -0.00099999994f : 0.00099999994f < t) {
        scale(d, d, -GetPointDistanceFromPlane(plane, p0) / t);
        add(out, p0, d);
    } else {
        GetPlaneFittingPoint(out, plane, p1);
    }
}

void nico_player_edgecolfit_Shoulder(int *obj)
{
    Vec4 pos;
    ColResult res;
    Vec4 g, a, b, c;
    EdgePts ev;
    GeoPtr gc;
    Vec4 pl, hp, e;
    ColResult2 res2;
    Vec4 k, m, n;
    int actor;
    char *cc;
    char *cc2;
    register char *gp asm("s5");
    char *h;
    int r;
    int changed;
    int fl;
    Vec4 *p;
    GeoPtr *gq;
    float zero;

    actor = obj[0];
    cc = GetCharacterClass(actor);
    B_0018B804 = 0;
    gp = cc + 0xC0;
    if (*(int *)(cc + 0x124) != 0) {
        h = *(char **)(cc + 0x1C4);
        if (h == 0 || (r = dldResolve((unsigned int *)(h + 8)), !(*(float *)(cc + 0x724) < 1.0f)) || r == MotRootDyn_EDGEXZ || r == MotRootDyn_EDGEPOINT) {
            if (*(int *)(gp + 0x30) == 4) {
                axisZ(&a, *(void **)(cc + 0x13C));
                axisY(&b, *(void **)(cc + 0x13C));
                scale(&a, &a, 0.19999999f);
                scale(&b, &b, 0.19999999f);
                GetGeometryPointerPosition(&g, gp);
                sub(&g, &g, &a);
                add(&g, &g, &b);
                axisX(&c, *(void **)(cc + 0x13C));
                zero = 0.0f;
                if (((int (*)(void *, int, int, void *, void *, float, float, float, float, void *))charrootdyn_detectCharClimbableWall)(&res, GetGeometryPointerCollisionDB(gp), 1, B_0018B7B0, &g, 0.29999999f, 0.5f, 0.5f, zero, cc + 0xE20)) {
                    p = &res.pos;
                    if (!(zero <= p->w))
                        p->w = zero;
                    __asm__ __volatile__("" : "+r"(p));
                    { float w = p->w; __asm__ __volatile__(""); if (!(w <= 1.0f)) p->w = 1.0f; }
                    GetGeometryPointerPosition(&pos, p);
                } else {
                    GetCollisionEdgePointerVertexPoint(&ev, gp);
                    changed = 0;
                    gq = &gc;
                    CopyGeometryPointer(gq, gp);
                    fl = gq->flag;
                    CompletePlaneD(&c, ev.p0);
                    if (GetPointDistanceFromPlane(&c, B_0018B7B0) < zero) {
                        if (fl != 0)
                            gq->t = zero;
                        else
                            gq->t = 1.0f;
                        changed = 1;
                    }
                    CompletePlaneD(&c, ev.p1);
                    if (0.0f < GetPointDistanceFromPlane(&c, B_0018B7B0)) {
                        if (fl != 0)
                            gq->t = 1.0f;
                        else
                            gq->t = 0.0f;
                        changed = 1;
                    }
                    if (changed) {
                        GetGeometryPointerPosition(&pos, gq);
                    } else {
                        CompletePlaneD(&c, B_0018B7B0);
                        intersect(&pos, &c, ev.p0, ev.p1, &pl);
                    }
                    sub(&pl, ev.p0, ev.p1);
                    CompletePlaneD(&pl, *(void **)(cc + 0x134));
                    intersect(&hp, &pl, ev.p0, ev.p1, &e);
                    cc2 = GetCharacterClass(actor);
                    axisY(&k, *(void **)(cc + 0x13C));
                    scale(&k, &k, 0.01f);
                    add(&m, &hp, &k);
                    add(&n, &pos, &k);
                    if (ClipCollisionFinderCallBack(&res2, &m, &n, cc2 + 0xE20, character_ikcolattrfilter, 0)) {
                        sub(&pos, &res2.pos, &k);
                        sub(&k, &m, &n);
                        normalize(&k, &k);
                        scale(&k, &k, 0.034999997f);
                        add(&pos, &pos, &k);
                    }
                }
                matVec(&res.v, (char *)obj + 0x70, B_0018B7C0);
                { float z = 0.0f; res.v.w = z; res.v.x = z; }
                matVec(&res.v, (char *)obj + 0x30, &res.v);
                add(&pos, &pos, &res.v);
                B_0018B800 = func_00091CE0(obj, &pos, B_0018B7B0, B_0018B7F0, B_0018B7E0, 0);
                B_0018B804 = 1;
            }
        }
    }
}
