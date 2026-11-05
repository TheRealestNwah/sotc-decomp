struct ThreadParam {
    int status;
    void (*entry)(void *);
    void *stack;
    int stackSize;
    int gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
};
/* The volatile accesses reproduce the Original's instruction order: the
   stack size is read twice, and the stack store is scheduled before the sum. */
struct Info {
    char buf[0x40];
    volatile int val;
};

extern struct Info *func_001013C8(const char *name);
extern void *memset(void *s, int c, unsigned int n);
extern int CreateThread(struct ThreadParam *param);
extern void LoaderSysEntryExternalThreadList(int thread);
extern int StartThread(int thread, void *arg);
extern void _execProgWithThread(void *arg);
extern char D_00141D70[];
extern int D_00139E04;

static inline unsigned int alignUp(unsigned int x, unsigned int a) {
    return (x + a - 1) / a * a;
}

void *execProgWithThread(const char *name, int prio) {
    struct ThreadParam tp;
    struct ThreadParam param;
    struct Info *info;
    int thread;
    int gp;
    int sz;
    unsigned int stk;

    info = func_001013C8(name);
    if (info == 0) {
        return 0;
    }
    memset(&param, 0, sizeof(param));
    param.entry = _execProgWithThread;
    stk = alignUp(D_00139E04, 16);
    sz = info->val;
    *(void * volatile *)&param.stack = (void *)stk;
    D_00139E04 = stk + sz;
    param.stackSize = (int)info->val;
    /* An assembler la: gcc would schedule the lui/addiu pair apart. */
    __asm__("la %0, D_00141D70" : "=r"(gp));
    param.gpReg = gp;
    param.initPriority = prio;
    tp = param;
    thread = CreateThread(&tp);
    LoaderSysEntryExternalThreadList(thread);
    StartThread(thread, info);
    return tp.stack;
}
