/* Parked: 18 diffs, same length. Remaining: gcc swaps $s0 and $s1 (the Original keeps the thread in $s0 and the hit position address in $s1), and the Original sets the hit position address in the delay slot of the CheckUnderVariableXZSurface result branch. */
#ifdef NONMATCHING
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int ControlMode_PLAYER_JUMP;
extern int ControlMode_PLAYER_RUN_FALL;
extern int *ScriptCtrlDef_SCRPlayerDive;
extern float YUnitVector[];
extern char gcGlobalVar[];
extern int CheckUnderVariableXZSurface(void *, void *, float *, void *);
extern int SCRGetCollision(void *, void *, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecLength(float *v)
{
    float len;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static void func_00076338(char *obj)
{
    float v[4] __attribute__((aligned(16)));
    struct {
        char pad[0x40];
        float pos[4];
    } hit __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    char col[0x40] __attribute__((aligned(16)));
    void *th;
    int mode;
    float len, r;

    th = isysGetThisSubThread();
    mode = *(int *)(GetCharacterClass(th) + 0x750);
    if (mode == ControlMode_PLAYER_JUMP || mode == ControlMode_PLAYER_RUN_FALL) {
        vecScale(v, YUnitVector, -*(float *)(*(char **)(obj + 0x184) + 0x34));
        vecAdd(v, v, *(float **)(GetLayoutClass(th) + 0x134));
        v[3] = 1.0f;
        if (CheckUnderVariableXZSurface(&hit, *(void **)(GetLayoutClass(th) + 0x134), v, gcGlobalVar + 0x230)) {
            vecSub(d, hit.pos, *(float **)(GetLayoutClass(th) + 0x134));
            len = vecLength(d);
            r = *(float *)(*(char **)(obj + 0x184) + 0x38);
            if (r * r < len) {
                if (SCRGetCollision(col, *(void **)(GetLayoutClass(th) + 0x134), hit.pos, gcGlobalVar + 0x230) == 0)
                    CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerDive[1]);
            }
        }
    }
}
#endif
