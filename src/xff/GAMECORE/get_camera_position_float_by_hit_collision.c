/* Parked draft: pulls a camera position toward a target, clipped by collision. Takes the vector
   from the camera point to the target, rescales it by the VU0 distance factor, builds the judge
   callback list (optional extra object and, when requested, the current camera target), collects
   collision DB data and clips the segment; returns whether a hit was found and writes the clipped
   (or unclipped) position. Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int ClipCollisionFinderWithVariableKeepCB(Vec4 *, Vec4 *, Vec4 *, int);
extern void ConstructorCollisionObjectJudgeCallbackData(int *);
extern void GetCollisionDBCallBack(int, int, Vec4 *, Vec4 *, float, int *);
extern float get_camera_collision_data_base_filter_radius(int, float, float, float);
extern int get_camera_move_collision_group(int);
extern int get_cur_camera_target(int, int);

static inline float lengthVu(Vec4 *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vsqrt Q, vf7w
"
                         "vwaitq
"
                         "cfc2 $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

int get_camera_position_float_by_hit_collision(Vec4 *out, Vec4 *from, Vec4 *to, int group, float p0, float p1,
                                               int owner, int extra, int useTarget)
{
    Vec4 seg __attribute__((aligned(16)));
    Vec4 clipped __attribute__((aligned(16)));
    float fl[2];
    int list[0x20];
    int hit;
    int g = get_camera_move_collision_group(owner);

    fl[0] = p0;
    fl[1] = p1;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&seg), "r"(to), "r"(from) : "memory");
    {
        float scale = lengthVu(&seg);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&seg), "r"(*(int *)&scale) : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(to), "r"(from), "r"(&seg) : "memory");
    ConstructorCollisionObjectJudgeCallbackData(&list[0]);
    if (extra != 0) {
        list[1 + list[0]] = extra;
        list[0]++;
    }
    if (useTarget == 1) {
        int t = get_cur_camera_target(owner, 1);
        if (t != 0) {
            list[1 + list[0]] = t;
            list[0]++;
        }
    }
    GetCollisionDBCallBack(group, g, &seg, &seg, get_camera_collision_data_base_filter_radius(owner, 0.1f, p0, p1), list);
    hit = ClipCollisionFinderWithVariableKeepCB(&clipped, &seg, &seg, group);
    if (hit != 1) {
        out->q = seg.q;
        hit = 0;
    } else {
        out->q = clipped.q;
    }
    return hit;
}
#endif
