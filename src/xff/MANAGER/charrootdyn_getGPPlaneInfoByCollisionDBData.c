typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern Vec4 *GetCollisionDBPlane(void *);
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern float GetPlaneSlopeDegree(Vec4 *);
extern void GetPlaneZTopYPlaneCoordQuaternion(Vec4 *, void *);
extern float GetTurnYAngleFromGlobalDir(Vec4 *, Vec4 *);

void charrootdyn_getGPPlaneInfoByCollisionDBData(char *ch, void *db)
{
    Vec4 quat;
    Vec4 dir;
    Vec4 *plane;
    unsigned long attr;
    void *rot;

    plane = GetCollisionDBPlane(db);
    attr = *GetCollisionDBAttributeAdr(db);
    *(unsigned long *)(ch + 0x698) = *(unsigned long *)(ch + 0x690) = attr;
    *(float *)(ch + 0x6B4) = GetPlaneSlopeDegree(plane);
    rot = *(void **)(ch + 0x13C);
    *(s128 *)(ch + 0x6A0) = plane->q;
    GetPlaneZTopYPlaneCoordQuaternion(&quat, plane);
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
                         : : "r"(&dir), "r"(rot) : "memory");
    *(float *)(ch + 0x6BC) = GetTurnYAngleFromGlobalDir(&quat, &dir);
}
