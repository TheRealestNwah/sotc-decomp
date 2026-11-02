extern int func_000599B8(void *, void *, void *, void *, void *, float, float, void *);
extern void *func_00059EA0(void *, void *);

int charrootdyn_detectCharClimbableWallContinue(void *a0, void *a1, void *a2, void *a3, void *a4, float f0,
                                                float f1, void *a5)
{
    int r = func_000599B8(a0, a1, a2, a3, a4, f0, f1, a5);

    if (r == 0) {
        void *next = func_00059EA0(a1, a5);
        if (next != 0)
            r = func_000599B8(a0, next, a2, a3, a4, f0, f1, a5);
    }
    return r;
}
