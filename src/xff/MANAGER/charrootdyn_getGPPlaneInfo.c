typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef union {
    s128 vector;
    long words[2];
} GeometryAttribute;

typedef struct {
    char pad0[0x13C];
    Vec4 *quaternion;
    char pad140[0x690 - 0x140];
    long attribute;
    long attributeCopy;
    Vec4 plane;
    char pad6B0[4];
    float slope;
    char pad6B8[4];
    float frontAngle;
} RootDynamics;

extern void GetGeometryPointerSurfaceAttribute(GeometryAttribute *, void *);
extern Vec4 *GetGeometryPointerSurfacePlane(void *);
extern float GetPlaneSlopeDegree(Vec4 *);
extern void GetPlaneZTopYPlaneCoordQuaternion(Vec4 *, void *);
extern float GetTurnYAngleFromGlobalDir(Vec4 *, Vec4 *);

void charrootdyn_getGPPlaneInfo(RootDynamics *root, void *geometry)
{
    Vec4 top, dir;
    GeometryAttribute attribute;
    Vec4 *q;
    Vec4 *plane;

    plane = GetGeometryPointerSurfacePlane(geometry);
    GetGeometryPointerSurfaceAttribute(&attribute, geometry);
    root->attribute = attribute.words[0];
    root->attributeCopy = attribute.words[0];
    root->slope = GetPlaneSlopeDegree(plane);
    q = root->quaternion;
    root->plane.q = plane->q;
    GetPlaneZTopYPlaneCoordQuaternion(&top, plane);
    __asm__ __volatile__("lqc2 vf04, 0(%1)
"
                         "vmul.xyzw vf05, vf04, vf04
"
                         "vmr32.xyzw vf06, vf04
"
                         "vmul.xyzw vf07, vf06, vf04
"
                         "vmr32.xyzw vf06, vf06
"
                         "vmul.xyzw vf08, vf06, vf04
"
                         "vsubx.z vf06, vf00, vf05x
"
                         "vsuby.z vf06, vf06, vf05y
"
                         "vaddw.y vf06, vf07, vf07w
"
                         "vsuby.x vf06, vf08, vf08y
"
                         "vsub.w vf06, vf00, vf00
"
                         "vadd.w vf05, vf00, vf00
"
                         "vmulw.xyz vf06, vf06, vf05w
"
                         "vaddw.z vf06, vf06, vf00w
"
                         "sqc2 vf06, 0(%0)
"
                         : : "r"(&dir), "r"(q) : "memory");
    root->frontAngle = GetTurnYAngleFromGlobalDir(&top, &dir);
}
