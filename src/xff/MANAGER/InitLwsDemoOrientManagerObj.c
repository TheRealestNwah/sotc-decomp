#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef int s128 __attribute__((mode(TI)));
typedef struct { s128 q; } Q;
typedef struct { Q q; int pad; float *f; } Orient;
typedef struct { char pad[0x90]; int b0; int b4; } Sub;
extern void initScriptObj(void *, int *, int);
extern int SetDemoMotionOrientInfo(Orient *, int, Q *);
extern void isysInitGroup(void *);
extern void func_0007E2D0(void *, int, Orient *, void *, int, float);

void InitLwsDemoOrientManagerObj(char *obj, int *script)
{
    Sub *sub = (Sub *)(obj + 0x20);
    void *group = obj + 0xB8;
    Orient *orient = (Orient *)(obj + 0x90);
    int info;

    initScriptObj(obj, script, *(int *)obj);
    info = SetDemoMotionOrientInfo(orient, script[9], (Q *)script[10]);
    sub->b0 = 0;
    orient->q = *(Q *)script[10];
    sub->b4 = 0;
    isysInitGroup(group);
    func_0007E2D0(group, info, orient, obj, orient->f[1] < -2.0f ? 5 : 4, 0.0f);
}
#endif
