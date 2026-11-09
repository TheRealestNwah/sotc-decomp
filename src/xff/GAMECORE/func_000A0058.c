#ifdef NONMATCHING
/* 92 diffs, same length (97 words). Semantics recovered (func_000A0058 + func_000A0198 tail): a ground-probe ray that updates w+0x7A0 and returns whether the actor is above ground. Remaining: gcc caches the L.result address in a saved register ($s2) and keeps both layout pointers in saved registers, so the frame is 0xD0 instead of 0xC0; empty-asm +r tricks on the result pointer did not remove it. Original recomputes sp+0x50 each use. */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4q;

extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void *memset(void *, int, unsigned int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int (*)(), int, int, int (*)(), int);
extern char *GetGeometryPointerCollisionDB(void *);
extern float *GetCollisionDBPlane(void *);
extern int AI_JudgeNotCharaObjFunc();
extern int AI_JudgeColAttrFunc();
extern char gcGlobalVar[];

static int func_000A0058(char *w)
{
    char *l0;
    char *l1;
    int hit;
    struct {
        s128 from;
        s128 to;
        s128 res30;
        long long a;
        long long b;
        char result[0x40];
        s128 resPlane;
    } L;
    int state = *(int *)(w + 0x274);

    if (state == 0xD)
        return 0;
    if (state == 0xC)
        return 0;
    if (*(int *)(w + 0x40) == 0)
        return 0;
    l0 = GetLayoutClass(isysGetThisSubThread());
    l1 = GetLayoutClass(isysGetThisSubThread());
    memset(&L.a, 0, 0x10);
    ((float *)&L.a)[1] = *(float *)(w + 0x7A0);
    ((long long *)&L.res30)[1] = L.b;
    ((long long *)&L.res30)[0] = L.a;
    L.from = L.to = **(s128 **)(l1 + 0x134);
    ((float *)&L.to)[1] -= *(float *)(*(char **)(w + 0x20) + 0xF8);
    if (ClipCollisionDirectCallBack((char *)L.result, &L.from, &L.to, gcGlobalVar + 0x230, AI_JudgeNotCharaObjFunc, 0, 0, AI_JudgeColAttrFunc, 0)) {
        float *plane = GetCollisionDBPlane(GetGeometryPointerCollisionDB((char *)&L.result[0]));

        if (0.70710677f < plane[1]) {
            hit = 1;
            L.res30 = L.resPlane;
        } else {
            hit = 0;
        }
    } else {
        hit = 0;
    }
    if (hit)
        *(float *)(w + 0x7A0) = ((float *)&L.res30)[1];
    {
        char *a = *(char **)(w + 0x20);

        if (*(float *)(a + 0xF4) < *(float *)(*(char **)(l0 + 0x134) + 4) - ((float *)&L.res30)[1] && *(int *)(a + 0x108) != 0)
            return 0;
        return 1;
    }
}
#endif
