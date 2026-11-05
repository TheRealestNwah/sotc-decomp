struct SemaParam {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
};

struct ThreadParam {
    int status;
    void (*func)(void *);
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    int current_priority;
    unsigned int attr;
    unsigned int option;
};

extern int CreateSema(struct SemaParam *sema);
extern int CreateThread(struct ThreadParam *thread);
extern int StartThread(int thread, void *arg);
extern void *sceCdPOffCallback(void (*func)(void *), void *addr);
extern void func_00104FF0(void *arg);
extern void D_001050A0(void *arg);
extern char D_0013DAC0[];
extern int D_0013A118;

void PreparePowerOff(void) {
    struct SemaParam sema;
    struct ThreadParam thread;

    sema.max_count = 1;
    sema.init_count = 0;
    sema.option = 0;
    D_0013A118 = CreateSema(&sema);
    thread.stack_size = 0x1000;
    /* The thread gp is taken with an asm la, which keeps the lui/addiu pair together. */
    { void *g; __asm__("la %0, D_00141D70" : "=r"(g)); thread.gp_reg = g; }
    thread.initial_priority = 1;
    thread.func = func_00104FF0;
    thread.stack = D_0013DAC0;
    StartThread(CreateThread(&thread), 0);
    sceCdPOffCallback(D_001050A0, 0);
}
