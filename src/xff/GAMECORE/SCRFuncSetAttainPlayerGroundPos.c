typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern int playerPlaneJudgeFunc();
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, int (*)(), int);
extern void setAttainmentPos(void *, void *);

void SCRFuncSetAttainPlayerGroundPos(void *obj, float h)
{
    char *w = getSCRDataCtrlWork(obj);
    Vec4 res[5];
    Vec4 to;

    to.q = **(s128 **)(*(char **)(w + 0x407C) + 0x134);
    to.f[1] = to.f[1] - h;
    if (ClipCollisionDirectCallBack(res, *(void **)(*(char **)(w + 0x407C) + 0x134), &to, gcGlobalVar + 0x230, 0, 0, 0,
                                    playerPlaneJudgeFunc, 0)) {
        res[4].f[1] = res[4].f[1] + 1.5f;
        setAttainmentPos(w, &res[4]);
    } else {
        setAttainmentPos(w, *(void **)(*(char **)(w + 0x407C) + 0x134));
    }
}
