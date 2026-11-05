#ifdef NONMATCHING /* 44 diffs: the original keeps the constant 1 in s3 across the call; here it is rematerialized */
extern int ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(void *, void *, void *);

static float func_000CBDE0(float *lenSq, void *diff, void *pos, char *obj)
{
    int type;
    int r;

    if (*(void **)(obj + 0x100) == 0)
        return 0.0f;
    if (*(int *)(*(char **)(obj + 4) + 4) == 0)
        return 1.0f;
    r = ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(0, *(void **)(obj + 0x100), pos);
    if (r != 1)
        return 0.0f;
    type = *(int *)(*(char **)(obj + 4) + 4);
    if (type != 4 && type != 1) {
        float d;
        __asm__ __volatile__(
            "lqc2 vf5, 0x0(%1)\n"
            "lqc2 vf6, 0x0(%2)\n"
            "vsub.xyz vf5, vf5, vf6\n"
            "sqc2 vf5, 0x0(%0)\n"
            : : "r"(diff), "r"(pos), "r"(obj + 0xB0) : "memory");
        __asm__ __volatile__(
            "lqc2 vf7, 0x0(%1)\n"
            "vmul.xyz vf7, vf7, vf7\n"
            "vaddy.x vf7, vf7, vf7y\n"
            "vaddz.x vf7, vf7, vf7z\n"
            "qmfc2 $2, vf7\n"
            "mtc1 $2, %0\n"
            : "=f"(d) : "r"(diff) : "$2");
        *lenSq = d;
    }
    return 1.0f;
}
#endif
