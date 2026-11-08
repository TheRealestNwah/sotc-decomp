typedef struct {
    char pad0[8];
    unsigned int next;
    unsigned int pad0C : 24;
    unsigned int flag : 1;
    unsigned int cb;
    unsigned int arg;
} GarbageNode;

extern int B_0004F5F8;
extern GarbageNode *gbPtn;
extern void WaitSema(int);
extern void SignalSema(int);
extern void *func_00001910(GarbageNode *, GarbageNode *, GarbageNode *);

#ifdef NONMATCHING
/* Parked: 4 words differ (v1/s1 for gbPtn in the first node load) */
void iosMallocGarbageTickProc(int (*fn)(void *), void *arg)
{
    GarbageNode *n;
    GarbageNode *next;

    WaitSema(B_0004F5F8);
    n = gbPtn;
    n = (GarbageNode *)((n->next & 0xFFFFFF) << 2);
    while (n != 0 && fn(arg)) {
        next = (GarbageNode *)((n->next & 0xFFFFFF) << 2);
        if (!(n->flag & 1) && next != 0 && (next->flag & 1)) {
            unsigned int cb = next->cb & 0xFFFFFF;
            if (cb != 0xFFFFFF) {
                void (*f)(void *, void *) = (void (*)(void *, void *))(cb << 2);
                void *a = (void *)((next->arg & 0xFFFFFF) << 2);
                void *r = func_00001910(n, next, gbPtn);
                if (f) f(a, r);
                next = (GarbageNode *)((n->next & 0xFFFFFF) << 2);
            }
        }
        n = next;
    }
    SignalSema(B_0004F5F8);
}
#endif
