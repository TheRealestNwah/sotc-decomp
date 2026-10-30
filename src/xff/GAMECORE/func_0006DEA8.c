typedef float Vec4[4] __attribute__((aligned(16)));

extern char *GetLayoutClass(void *);
extern void *GAMEUTIL_get_player_obj(void);
extern void *GAMEUTIL_get_riding_horse_object(void *);
extern int SkelFocusDef_WORM_HEAD1;
extern int GetSkeletonFocusNodeDirect(int);
extern void GAMEUTIL_get_node_posi_by_id(float *, void *, int);
extern void GAMEUTIL_get_local_directionZ(float *, void *);

static inline void vecScale(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float distXZ2(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static void func_0006DEA8(void *obj)
{
    Vec4 pos;
    Vec4 dir;
    char *layout = GetLayoutClass(obj);
    void *player = GAMEUTIL_get_player_obj();
    float range;
    float offset;
    int state;

    if (player == 0) {
        *(int *)(layout + 0x1AC) = 0;
        return;
    }
    offset = 10.0f;
    state = *(int *)(layout + 0x1AC);
    if (GAMEUTIL_get_riding_horse_object(player) == 0) {
        range = 30.0f;
        if (state == 10)
            range = 45.0f;
    } else {
        range = 20.0f;
        if (state == 10)
            range = 25.0f;
    }
    GAMEUTIL_get_node_posi_by_id(pos, obj, GetSkeletonFocusNodeDirect(SkelFocusDef_WORM_HEAD1));
    GAMEUTIL_get_local_directionZ(dir, obj);
    vecScale(dir, offset);
    vecAdd(pos, pos, dir);
    if (distXZ2(pos, *(float **)(GetLayoutClass(player) + 0x134)) <= range * range)
        *(int *)(layout + 0x1AC) = 10;
    else
        *(int *)(layout + 0x1AC) = 0;
}
