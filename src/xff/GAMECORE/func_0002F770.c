/* Parked: 14 diffs, same size (424 words). BGM slot state machine: steps the 3 entries of B_001887D0 through standby (1-2), delayed start with bgmPlay/bgmChangeVol plus onPlay script and caption (3), per-tick volume control from distance and conditions with end-mode checks (4), bgmStop (5) and slot release (6). Remaining: register choice only. The caption handle address lives in a1 in the Original (v1 here), and the %hi of D_0017A968 in firstObj uses a0 in the Original (a1 here). */
#ifdef NONMATCHING
typedef struct Entry {
    unsigned int bgm;
    unsigned int caption;
    unsigned int handle;
    int once;
    float limit;
    char p14[0xC];
    float delay;
    float vol2;
    unsigned int onPlay;
    unsigned int volCtrl;
    unsigned int onTick;
    int endMode;
    float endTime;
    float fade;
    int busy;
    unsigned int flags;
    char p48[8];
} Entry;

typedef struct Play {
    int state;
    int prio;
    int arg;
    int done;
    float start;
    int count;
    int *hnd;
    int owner;
    void *ctx;
    float f24;
    int f28;
    int f2C;
    void (*cb)(struct Play *);
    float vol;
    long long mode;
} Play;

typedef struct Cond {
    unsigned int h;
    float mul;
} Cond;

typedef struct VolCtrl {
    int kind;
    int vol;
    float f8;
    float lo;
    float hi;
    Cond cond[3];
} VolCtrl;

extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern int gstatKaisouMode;
extern int D_0017A938;
extern int D_0017A960;
extern void *D_0017A968;
extern Play B_001887D0[3];
extern int bgmChkStandbyComplete(int *);
extern void bgmPlay(int *, float);
extern void bgmChangeVol(int *, float, float);
extern void bgmStop(int *, int *, float);
extern void execSCRBaseFunc(void *, unsigned int *);
extern int execCondition(void *, Cond *);
extern void *SCRGetFirstObj(void *);
extern void DisplayCaptionTableChild(unsigned int *, void *, int);
extern char *getSCRDataCtrlWork(void);

static inline int *dldBase(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static inline void *firstObj(void)
{
    if (D_0017A960 == 0) {
        D_0017A960 = 1;
        D_0017A968 = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    }
    return D_0017A968;
}

static inline void stopPlay(Play *p)
{
    Entry *o = (Entry *)p->owner;
    o->flags &= ~2;
    o->flags &= ~1;
    p->state = 5;
    ((Entry *)p->owner)->busy = 0;
}

static inline void finish(Play *p)
{
    int st = p->state;
    if (st != 5 && st != 6)
        stopPlay(p);
    if (p->cb != 0)
        p->cb(p);
}

static inline void updateMax(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (B_001887D0[i].state == 0) {
            D_0017A938 = 0;
            return;
        }
        D_0017A938 = B_001887D0[i].prio < D_0017A938 ? B_001887D0[i].prio : D_0017A938;
    }
}

#define NOW (*(float *)(gcGlobalVar + 0x178))

static void func_0002F770(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        Play *p = &B_001887D0[i];
        if (p->state == 0)
            continue;
        switch (p->state) {
        case 1:
            if (!bgmChkStandbyComplete(p->hnd))
                break;
            if (p->arg != 0) {
                p->state = 2;
                break;
            }
            goto start;
        case 2:
            if (p->arg != 0)
                break;
        start:
            p->state = 3;
            p->start = NOW;
            break;
        case 3: {
            Entry *e = (Entry *)p->owner;
            int go = 1;
            if (e->delay != 0.0f && NOW - p->start < e->delay)
                go = 0;
            if (!go)
                break;
            p->start = NOW;
            bgmPlay(p->hnd, 0.0f);
            bgmChangeVol(p->hnd, p->vol, ((Entry *)p->owner)->vol2);
            p->state = 4;
            if (dldResolve(&((Entry *)p->owner)->onPlay) != 0)
                execSCRBaseFunc(p->ctx, &((Entry *)p->owner)->onPlay);
            if (dldResolve(&((Entry *)p->owner)->caption) != 0) {
                void *obj = firstObj();
                if (obj != 0 && gstatKaisouMode == 0)
                    DisplayCaptionTableChild(&((Entry *)p->owner)->caption, obj, 1);
            }
            break;
        }
        case 4: {
            Entry *e = (Entry *)p->owner;
            VolCtrl *v = (VolCtrl *)dldResolve(&e->volCtrl);
            if (v != 0) {
                float t = 0.0f;
                float m;
                int j;
                if (v->kind == 0) {
                    if (firstObj() != 0) {
                        t = *(float *)(getSCRDataCtrlWork() + 0x4080);
                        e = (Entry *)p->owner;
                    } else {
                        finish(p);
                        break;
                    }
                }
                if (dldResolve(&e->onTick) != 0)
                    execSCRBaseFunc(p->ctx, &((Entry *)p->owner)->onTick);
                if (t < v->lo)
                    m = 1.0f;
                else if (v->hi <= t)
                    m = 0.0f;
                else
                    m = 1.0f - (t - v->lo) / (v->hi - v->lo);
                for (j = 0; j < 3; j++) {
                    Cond *c = &v->cond[j];
                    if (dldBase(&c->h) != 0 && dldBase(&c->h) != DldSysUndefSymbol && execCondition(p->ctx, c))
                        m *= c->mul;
                }
                bgmChangeVol(p->hnd, m * (float)v->vol, v->f8);
                e = (Entry *)p->owner;
            }
            if (e->endTime != 0.0f) {
                switch (e->endMode) {
                case 2:
                    if ((float)p->count >= e->endTime)
                        finish(p);
                    break;
                case 3:
                    if (e->endTime <= NOW - p->start)
                        finish(p);
                    break;
                case 4:
                    if (p->count > 0)
                        finish(p);
                    break;
                }
            }
            break;
        }
        case 5:
            bgmStop(p->hnd, &p->done, p->f24);
            p->state = 6;
            break;
        case 6:
            if (p->done != 0) {
                p->state = 0;
                p->owner = 0;
                p->prio = 0;
                updateMax();
            }
            break;
        }
    }
}
#endif
