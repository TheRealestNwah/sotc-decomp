/* BGM entry selector: keeps the current slot while its entry stays valid (keep flag, condition, or play time under the limit), otherwise stops it and starts the first entry whose condition holds through func_0002E220, reusing a pending slot when it matches *last. */
typedef struct Play Play;

typedef struct Entry {
    char p0[0x14];
    unsigned int cond;
    int keep;
    float limit;
    char p20[0x20];
    Play *busy;
    unsigned int flags;
    char p48[8];
} Entry;

struct Play {
    int state;
    int prio;
    int arg;
    char pC[0x10];
    int owner;
    char p20[0xC];
    float t;
};

extern char gcGlobalVar[];
extern int execCondition(void *, unsigned int *);
extern Play *func_0002E220(Entry *, int, int, void *, int, void (*)(Play *), float);

static inline void stopPlay(Play *p)
{
    if ((unsigned)(p->state - 5) >= 2) {
        Entry *o = (Entry *)p->owner;
        o->flags &= ~2;
        o->flags &= ~1;
        p->state = 5;
        ((Entry *)p->owner)->busy = 0;
    }
}

static void func_0002E7A8(Entry *e, int n, int prio, Play **cur, Play **last, void *ctx, int a6, void (*cb)(Play *))
{
    Play *p = *cur;
    int i;

    if (p != 0 && p->state == 1)
        return;
    i = 0;
    if (n > 0) {
        do {
            Play *b;
            if (p != 0 && (Entry *)p->owner == e) {
                if (e->keep != 0)
                    break;
                if (execCondition(ctx, &e->cond) == 0) {
                    { char *g = gcGlobalVar; p->t += *(float *)(g + 0x180); }
                    if (!(e->limit < p->t))
                        break;
                    stopPlay(p);
                    p = 0;
                } else {
                    p->t = 0.0f;
                    break;
                }
            }
            b = e->busy;
            if (!(e->flags & 1)) {
                if (b != 0 && b != *last)
                    goto next;
                if (execCondition(ctx, &e->cond) == 0)
                    goto next;
            }
            if (p != 0)
                stopPlay(p);
            if (b != 0 && b == *last) {
                p = b;
                p->arg = 0;
                *(int *)last = 0;
                e->flags &= ~2;
                e->flags &= ~1;
                break;
            }
            p = func_0002E220(e, prio, 0, ctx, a6, cb, 100.0f);
            if (p == 0 && e->keep != 0)
                e->flags |= 1;
            break;
        next:
            i++;
            e++;
        } while (i < n);
    }
    *cur = p;
}
