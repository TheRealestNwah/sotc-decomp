/* Demo-camera script thread started by PlayDemoCameraOrient: resolves the first orient
 * resource, starts its LWS animation through func_00010A88 and then, every frame, advances
 * the camera time from the VInt clock (scaled by the object's speed), fast-forwards the
 * demo manager on request, fires each cut's finish callback once, and at a cut's end moves
 * to the next orient, flags the group's characters (9) and orient managers (29) as cut
 * finished and starts the next animation. When the orients run out it ends the animation
 * and keeps feeding the effect manager forever.
 * Parked at 7 diffs: the cut argument's lwc1 is scheduled one slot early, and the two
 * spill slots for &obj->anim (0x34, 0x38) are swapped between the animation-end and the
 * next-cut uses. */
#ifdef NONMATCHING
extern int *DldSysUndefSymbol;
extern struct { char pad[0x1AC]; int demoSync; } gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern unsigned int *SetDemoMotionOrientInfo(void *, int, void *);
extern unsigned int *GetDemoOrientNext(void *);
extern void setVIntrBaseTime(void *);
extern float getVIntrDiffTime(void *);
extern void addVIntrTime(void *, float);
extern int IsForwardTime__DemoMan(int, float);
extern void ForwardTime__DemoMan(int, float);
extern int end_camera_lws_animation(int);
extern void fsEffectManagerSetDemoParam(void *);
extern void scrRun(void);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void SetCharacterObjDemoCutFinishFlag(void *, int);
extern void SetLwoDemoOrientManagerObjCutFinishFlag(void *, int);
extern int func_00010A88(int *, void *, char *, void *);

typedef struct {
    float arg;
    void (*func)(float);
    int done;
} DemoCutCallback;

typedef struct {
    unsigned int pad0;
    unsigned int lws;
    unsigned int caption;
    unsigned int effect;
    char pad10[0x10];
    DemoCutCallback cut;
} DemoRes;

typedef struct {
    char pad0[0x14];
    unsigned int *handle;
    char pad18[8];
} OrientInfo;

typedef struct {
    char pad0[0x10];
    float pos[4];
    int f20;
    int f24;
    int f28;
    int anim;
    int forward;
    int demo;
    int finished;
    float time;
    int cut;
    float speed;
} DemoCamObj;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline void fireCut(DemoCutCallback *cb, float arg, int flag)
{
    void (*f)(float) = cb->func;
    if (cb->done == 0 && f != 0) {
        f(arg);
        cb->done = flag;
    }
}

void func_00010CB0(DemoCamObj *self)
{
    DemoCamObj *obj;
    OrientInfo info;
    struct { int a, b, c, d; } vt;
    void *thread;
    int *anim;
    int *animp;
    unsigned int *h;
    unsigned int *h0;
    DemoRes *res;
    DemoRes *r;
    DemoRes *first;
    float margin;
    float cur;
    float t;
    float frames;
    float end;
    float start;
    float zero;
    int forwarded;
    void **it;
    unsigned char *o;
    DemoCutCallback *cb;
    float arg;
    int on;

    thread = isysGetThisSubThread();
    cur = 0.0f;
    h0 = SetDemoMotionOrientInfo(&info, self->f24, self->pos);
    setVIntrBaseTime(&vt);
    if (h0 == 0)
        return;
    first = (DemoRes *)dldResolve(h0);
    first->cut.done = 0;
    obj = self;
    frames = func_00010A88(&obj->anim, first, (char *)obj, thread);
    obj->cut = 0;
    start = zero = 0.0f;
    end = frames + start;
    animp = &obj->anim;
    for (;;) {
        if (gcGlobalVar.demoSync != 0)
            addVIntrTime(&vt, cur * (1.0 / (obj->speed * 29.427792915531334)));
        forwarded = 0;
        t = getVIntrDiffTime(&vt) * (obj->speed * 29.427792915531334);
        cur = end * 0.033333335f;
        if (obj->forward != 0 && IsForwardTime__DemoMan(obj->demo, cur)) {
            forwarded = 1;
            ForwardTime__DemoMan(obj->demo, cur);
            obj->forward = 0;
        }
        r = (DemoRes *)dldResolve(info.handle);
        res = r;
        cb = &res->cut;
        arg = cb->arg;
        on = 1;
        margin = arg * 30.0f;
        if (t - start < zero || frames - margin < t - start)
            fireCut(cb, arg, on);
        if (end <= t || forwarded) {
            cb = &r->cut;
            fireCut(cb, cb->arg, 1);
            h = GetDemoOrientNext(&info);
            if (h == 0) {
                end_camera_lws_animation(*animp);
                *animp = -1;
                obj->finished = 1;
                for (;;) {
                    fsEffectManagerSetDemoParam(dldResolve(&r->effect));
                    scrRun();
                }
            }
            o = 0;
            for (it = isysGroupForFirst(obj, 0); it != 0; it = isysGroupForNext(it, 0)) {
                o = *it;
                switch (o[8]) {
                case 9:
                    SetCharacterObjDemoCutFinishFlag(o, 1);
                    break;
                case 29:
                    SetLwoDemoOrientManagerObjCutFinishFlag(o, 1);
                    break;
                }
            }
            if (o != 0)
                isysGroupForExit(o, 0);
            start = end;
            if (forwarded) {
                addVIntrTime(&vt, end * (1.0 / (obj->speed * 29.427792915531334)));
                t = end;
            }
            res = (DemoRes *)dldResolve(h);
            res->cut.done = 0;
            frames = func_00010A88(&obj->anim, res, (char *)obj, thread);
            obj->cut++;
            end += frames;
        }
        fsEffectManagerSetDemoParam(dldResolve(&res->effect));
        cur = t;
        obj->time = cur;
        scrRun();
    }
}
#endif
