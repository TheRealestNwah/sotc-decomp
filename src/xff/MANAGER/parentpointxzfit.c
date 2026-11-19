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
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern void charrootdyn_getCollisionDB(void *, void *, int, void *, void *, int, float);
extern void charrootdyn_getInterpVector(void *, void *, void *, float);
extern void charrootdyn_getInterpPoint(void *, s128 *, void *, float);
extern void charrootdyn_restoreposition(void *, int, void *, void *, void *, int);
extern void charrootdyn_parentpointxzfitstab(char *, int, int);
extern int charrootdyn_slidecollision(void *, void *, void *, void *, void *, int, int, float, float);
extern void charrootdyn_setkeepcolhitstatus(char *, void *, void *, void *, void *, float);
extern int *GetGeometryPointerCollisionDB(void *);
extern char *GetLayoutClass(int);
extern void ForceUnparentLayoutObj(int);
extern void charrootdyn_updateParentPointGPInfo(char *);
extern int charrootdyn_checkZplane(void *, char *, float);
extern void charrootdyn_setHColFindStatus(char *, void *, float);
extern int charrootdyn_getLandingSurface(void *, void *, void *, void *, float);
extern void charrootdyn_getWaterStatus(char *, void *, void *, void *, void *, float);
extern void charrootdyn_getvelocity(void *, void *, void *, float);

static inline void rotatePoint(void *point, void *quaternion, void *out)
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
                         : : "r"(out), "r"(point), "r"(quaternion) : "memory");
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

/* Parked at 8 diffs: the Original computes &L.off separately for the
   rotation output and for the later adds/subs (gcc CSEs them here, 6 words),
   and schedules the getWaterStatus self argument differently (2 words). */
#ifdef NONMATCHING
void parentpointxzfit(int id, float *vel, float t, float unused, float dt)
{
    struct {
        SlideResult r;
        s128 a;
        s128 b;
        s128 off;
    } L;
    char *cls;
    s128 *pos;
    s128 *quat;
    s128 *prev;
    char *geom;
    char *finder;
    char *db;
    float radius;
    int parent;
    int *pp;
    s128 *po;

    cls = GetCharacterClass(id);
    pos = *(s128 **)(cls + 0x134);
    geom = cls + 0x6D0;
    quat = *(s128 **)(cls + 0x13C);
    finder = cls + 0x4C0;
    radius = *(float *)(cls + 0xE34);
    pp = (int *)(cls + 0x1C0);
    parent = *pp;
    db = cls + 0xE20;
    prev = *(s128 **)(cls + 0x138);
    charrootdyn_updateCharacterClassParentGeometry(cls, &ZeroPoint, geom);
    charrootdyn_getRegularColFinderPosition(finder, cls, quat, pos);
    charrootdyn_getCollisionDB(db, *(char **)(cls + 0xE38) + *(short *)(cls + 0x370) * 4, id, finder, cls + 0x4D0, parent, radius);
    if (*(int *)(cls + 0x124) != 0) {
        charrootdyn_getInterpVector(geom, vel, geom, t);
        charrootdyn_getInterpPoint(cls + 0xB30, &ZeroPoint, cls + 0xB30, t);
        charrootdyn_restoreposition(pos, id, *(void **)(cls + 0x13C), pos, cls + 0x700, 0);
        charrootdyn_parentpointxzfitstab(cls, *pp, 0);
        rotatePoint(cls + 0xE00, quat, &L.off);
        po = &L.off;
        addXYZ(&L.a, prev, po);
        addXYZ(&L.b, pos, po);
        if (charrootdyn_slidecollision(&L.r, &L.a, &L.b, &ZeroVector, db, 0, parent, *(float *)(cls + 0xE0C), 0.01f) != 0) {
            charrootdyn_setkeepcolhitstatus(cls, &L.r.q20, &L.r, &L.r.q30, &L.r.q40, *(float *)(cls + 0x3E4));
            subXYZ(prev, &L.r.q10, po);
            subXYZ(pos, &L.r, po);
            if (*(int *)(*(char **)(GetLayoutClass(*GetGeometryPointerCollisionDB(cls + 0xC0)) + 0x174) + 0x20) < L.r.x80) {
                ForceUnparentLayoutObj(id);
                *(char *)(cls + 0x531) = 1;
                goto end;
            }
        }
        charrootdyn_updateParentPointGPInfo(cls);
    }
end:
    if (charrootdyn_checkZplane(&L.r, cls, 0.0f) != 0) {
        charrootdyn_setHColFindStatus(cls, &L.r, 0.0f);
    }
    if (charrootdyn_getLandingSurface(&L.r, db, prev, pos, -vel[2] - *(float *)(cls + 0x3E4)) != 0) {
        charrootdyn_setHColFindStatus(cls, &L.r, 0.0f);
    }
    charrootdyn_getWaterStatus(cls, &L.r, *(char **)(cls + 0xE38) + *(short *)(cls + 0x370) * 4, db, pos, -*(float *)(cls + 0x3DC));
    charrootdyn_getvelocity(cls + 0x30, pos, prev, dt);
}
#endif
