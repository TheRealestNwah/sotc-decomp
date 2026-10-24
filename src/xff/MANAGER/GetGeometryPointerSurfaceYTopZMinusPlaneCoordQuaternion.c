extern float YUnitVector[];
extern float *GetCollisionDBPlane(char *);
extern void GetPlaneTopDir(float *, float *);
extern void GetQuaternionByAxisDirZY(void *, float *, float *);

static inline float *getSurfacePlane(char *g)
{
    char *p;
    float *v;

    switch (*(int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        p = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
    default:
        p = 0;
        break;
    }
    v = YUnitVector;
    if (p != 0)
        v = GetCollisionDBPlane(p);
    return v;
}

void GetGeometryPointerSurfaceYTopZMinusPlaneCoordQuaternion(void *out, char *g)
{
    float top[4] __attribute__((aligned(16)));
    float minus[4] __attribute__((aligned(16)));
    float *plane = getSurfacePlane(g);
    float scale;

    GetPlaneTopDir(top, plane);
    scale = -1.0f;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(minus), "r"(plane), "r"(scale) : "memory");
    GetQuaternionByAxisDirZY(out, minus, top);
}
