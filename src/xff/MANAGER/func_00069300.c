/* Parked at 13 diffs: gcc swaps the callee-saved registers of the quaternion
   pointer and the collision callback ($s2/$s3, 11 words), and the address and
   data registers of the rotation input copy (2 words). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { char data[0x50]; } GeometryPointer;
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec4f;

extern Vec4 ZeroPoint;
extern char *GetCharacterClass(void *);
extern void charrootdyn_updateCharacterClassParentGeometry(char *, Vec4 *, char *);
extern int ClipCollisionFinderWithKeep4D(KeepResult *, void *, Vec4 *, char *, float);
extern void charrootdyn_getLimitMode(Vec4 *, char *);
extern void GetGeometryPointerPosition(Vec4 *, char *);
extern void *memset(void *, int, int);
extern int charrootdyn_getCyclicCollisionDetectZY(GeometryPointer *, Vec4 *, Vec4 *, int, char *, float);
extern void CopyGeometryPointer(GeometryPointer *, void *);
extern void ParentLayoutObj(void *, GeometryPointer *);
extern void charrootdyn_parentpointxzfitstab(char *, int, KeepResult *);
extern void *GetGeometryPointerSurfacePlane(char *);
extern void charrootdyn_getCompleteFittingYQFromYDir(Vec4 *, void *, Vec4 *);

static inline void rotatePoint(void *point, void *quaternion, void *out)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%0)
" : : "r"(point));
    __asm__ __volatile__(""
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
                         : : "r"(out), "r"(point), "r"(quaternion) : "memory");
}

static inline void subXZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xz vf5, vf5, vf6\n"
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

static inline void fitInline(void *id, Vec4 *quat, KeepResult *pt, void *keep)
{
    GeometryPointer g;
    Vec4 lim;
    Vec4 pos;
    Vec4f tmp;
    Vec4f v;
    Vec4f *dst;
    GeometryPointer g2;
    char *c2;
    char *gp;
    char *db;
    int (*fn)(void *, GeometryPointer *);
    float d;
    float z;
    float step;
    int i;
    int found;

    c2 = GetCharacterClass(id);
    gp = c2 + 0xC0;
    charrootdyn_getLimitMode(&lim, c2);
    GetGeometryPointerPosition(&pos, gp);
    memset(&v, 0, 0x10);
    v.x = pt->position.f[0];
    tmp = v;
    dst = &v;
    rotatePoint(&tmp, quat, dst);
    subXYZ(&pos, &pos, &v);
    db = c2 + 0xE20;
    z = -pt->position.f[2];
    if (charrootdyn_getCyclicCollisionDetectZY(&g, &pos, quat, 4, db, z) != 0) {
        fn = *(int (**)(void *, GeometryPointer *))(c2 + 0xA8C);
        if (fn != 0 && fn(id, &g) == 0) {
            d = z * 0.5f;
            step = d;
            found = 0;
            i = *(signed char *)(c2 + 0xA90);
            while (--i != -1) {
                int r = charrootdyn_getCyclicCollisionDetectZY(&g2, &pos, quat, 4, db, d);
                step *= 0.5f;
                if (r != 0 && fn(id, &g2) != 0) {
                    d += step;
                    found = 1;
                    CopyGeometryPointer(&g, &g2);
                } else {
                    d -= step;
                }
            }
            if (found == 0) {
                if (keep != 0) {
                    CopyGeometryPointer(&g, keep);
                } else {
                    CopyGeometryPointer(&g, gp);
                }
            }
        }
        ParentLayoutObj(id, &g);
        charrootdyn_parentpointxzfitstab(c2, *(int *)(c2 + 0x1C0), pt);
    } else if (*(int *)(c2 + 0x124) != 0) {
        charrootdyn_getCompleteFittingYQFromYDir(quat, GetGeometryPointerSurfacePlane(gp), quat);
        charrootdyn_parentpointxzfitstab(c2, *(int *)(c2 + 0x1C0), pt);
    }
}

static void func_00069300(void *id, Vec4 *target, void *keep)
{
    KeepResult pt;
    char *cls;
    char *geom;

    cls = GetCharacterClass(id);
    geom = cls + 0x6D0;
    charrootdyn_updateCharacterClassParentGeometry(cls, &ZeroPoint, geom);
    if (ClipCollisionFinderWithKeep4D(&pt, *(void **)(cls + 0x138), *(Vec4 **)(cls + 0x134), cls + 0xE20, *(float *)(cls + 0x3E4)) != 0) {
        (*(Vec4 **)(cls + 0x134))->q = pt.position.q;
    }
    subXZ(&pt, target, geom);
    fitInline(id, *(Vec4 **)(cls + 0x13C), &pt, keep);
}
#endif
