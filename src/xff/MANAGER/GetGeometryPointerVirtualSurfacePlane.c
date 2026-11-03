#ifdef NONMATCHING /* case 9 keeps &q in s0 instead of recomputing sp+0x10 */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    int unk0;
    int unk4;
    float unk8;
    char padC[0x24];
    int type;
} GeometryPointer;

extern Vec4 YUnitVector;
static void GetGeometryPointerPosition(Vec4 *, GeometryPointer *);
extern Vec4 *GetCollisionDBPlane(void *);
extern void GetClothQuaternion(Vec4 *, int, int, float, int);
extern void CompletePlaneD(Vec4 *, Vec4 *);

static inline void *GetGeometryPointerCollisionDB(GeometryPointer *g)
{
    switch (g->type) {
    case 2:
    case 3:
    case 4:
    case 5:
        return g;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        return 0;
    }
    return 0;
}

int GetGeometryPointerVirtualSurfacePlane(Vec4 *plane, GeometryPointer *g)
{
    Vec4 pos;
    Vec4 q;
    int ret = 0;

    switch (g->type) {
    case 2:
    case 3:
    case 4:
    case 5: {
        void *db = GetGeometryPointerCollisionDB(g);
        Vec4 *p = &YUnitVector;

        if (db != 0)
            p = GetCollisionDBPlane(db);
        plane->q = p->q;
        ret = 1;
        break;
    }
    case 9: {
        GetGeometryPointerPosition(&pos, g);
        GetClothQuaternion(&q, g->unk0, g->unk4, g->unk8, 0);
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
                             : : "r"(plane), "r"(&q) : "memory");
        CompletePlaneD(plane, &pos);
        break;
    }
    default: {
        GetGeometryPointerPosition(&q, g);
        plane->q = YUnitVector.q;
        CompletePlaneD(plane, &q);
        break;
    }
    }
    return ret;
}
#endif
