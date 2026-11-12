/* Parked draft: debug free-camera move step. Applies the first/second debug controller to the
   camera position, reads the right stick (squared with sign preserved) as a move vector in the
   camera's view space (scaled by frame time * 30), adds it to the position, chooses the focus
   point (the focus node of the layout's camera target, else its stored position) and returns
   whether the camera moved more than 0.01 (squared). Written from the m2c draft; not yet
   compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern char iosDefaultPadData[];
extern int padManagerData;
extern void DebugGlobalMoveWith1stController(Vec4 *);
extern void DebugGlobalMoveWith2ndController(Vec4 *, Vec4 *);
extern int GAMEUTIL_get_node_posi_by_id(Vec4 *, int, int);
extern char *GetLayoutClass(int);
extern void GetMoveVectorOnWV(Vec4 *, float *, float *, int, float);
extern int GetSkeletonFocusNodeDirect(int);
extern int get_main_cameraman_camera_obj(void);
extern void iosPadGetXZInputR(float *, void *);
extern void *memset(void *, int, unsigned int);

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

int func_000E45D0(Vec4 *pos, Vec4 *focus, int obj, Vec4 *src)
{
    Vec4 move __attribute__((aligned(16)));
    Vec4 node __attribute__((aligned(16)));
    float stick[8] __attribute__((aligned(16)));
    float v1[4] __attribute__((aligned(16)));
    float v2[4] __attribute__((aligned(16)));
    char *layout;
    char *cam;
    char *target;
    Vec4 pick;
    float x;
    float y;

    if (padManagerData & 1)
        DebugGlobalMoveWith1stController(src);
    else
        pos->q = src->q;
    DebugGlobalMoveWith2ndController(pos, pos);
    cam = GetLayoutClass(get_main_cameraman_camera_obj());
    memset(v1, 0, 0x10);
    memset(v2, 0, 0x10);
    iosPadGetXZInputR(stick, iosDefaultPadData + 0x78);
    x = stick[0] < 0.0f ? stick[0] * -stick[0] : stick[0] * stick[0];
    y = stick[2] < 0.0f ? stick[2] * -stick[2] : stick[2] * stick[2];
    stick[0] = x;
    stick[2] = y;
    v1[0] = -x;
    if (padManagerData & 1)
        v1[2] = y;
    GetMoveVectorOnWV(&move, v1, v2, *(int *)(cam + 0x164), *(float *)(gcGlobalVar + 0x170) * 30.0f);
    addXYZ(pos, pos, &move);
    layout = GetLayoutClass(obj);
    target = *(char **)(layout + 0x1A8);
    if (target == 0 || GAMEUTIL_get_node_posi_by_id(&node, obj, GetSkeletonFocusNodeDirect(*(int *)(target + 8))) != 1)
        pick.q = **(s128 **)(layout + 0x134);
    else
        pick.q = node.q;
    focus->q = pick.q;
    return distSq(pos, &move) > 0.01f;
}
#endif
