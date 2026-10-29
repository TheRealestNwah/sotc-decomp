typedef int Qword __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
static inline void subtract3(Vector out, Vector a, Vector b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vsub.xyz vf5, vf5, vf6\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline float length3(Vector a)
{
    float result;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n" "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n" "vmadday.w ACC, vf0, vf7y\n" "vmaddz.w vf7, vf0, vf7z\n" "vsqrt Q, vf7w\n" "vwaitq\n" "cfc2 $2, $vi22\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(a) : "$2");
    return result;
}
static inline void scale3(Vector out, Vector a, float t)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n" "qmtc2 %2, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(a), "r"(t) : "memory");
}
static inline void add3(Vector out, Vector a, Vector b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vadd.xyz vf5, vf5, vf6\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(a), "r"(b) : "memory");
}

extern int get_player_collision_group_cameraman(void *);
extern int func_000D5C88();
extern int CollisionPlaneJudgeCallbackCameraLeave();
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), int);
int is_hit_cam_opt_leave_collision_attribute(Vector out, Vector from, Vector to, void *camera)
{
    Vector result[5];
    Vector start, end, delta;
    int hit;
    subtract3(delta, to, from);
    scale3(delta, delta, 0.5f / length3(delta));
    subtract3(start, from, delta);
    add3(end, to, delta);
    hit = ClipCollisionDirectCallBack(result, start, end,
        get_player_collision_group_cameraman(camera), func_000D5C88, 0, 0,
        CollisionPlaneJudgeCallbackCameraLeave, 0);
    if (hit == 1) {
        *(Qword *)out = *(Qword *)result[4];
        return 1;
    }
    return 0;
}
