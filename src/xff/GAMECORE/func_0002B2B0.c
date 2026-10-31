typedef struct {
    int task;
} GroupEntry;

typedef struct {
    char pad0[0x20];
} LoadReq;

extern int D_0017A868;
extern int D_0017A86C;
extern int D_0017A870;
extern char B_00188650[];
extern char B_00188668[];
extern char B_00188730[];
extern void initSlowManager(void);
extern int CheckCamFinalizerReady(void);
extern void scrRun(void);
extern GroupEntry *isysGroupForFirst(void *group, int flag);
extern GroupEntry *isysGroupForNext(GroupEntry *e, int flag);
extern void isysGroupForExit(int task, int flag);
extern void func_000283D8(LoadReq *, void *);
extern void func_0002ABB0(void *, LoadReq *, void (*)(void), void (*)(void), int);
extern void func_0002AEA8(LoadReq *, void *);
extern void func_0002D480(void);
extern void func_0002D4F8(void);
extern void func_00027588(void);
extern void func_00027778(void);

static void func_0002B2B0(void)
{
    LoadReq req;
    LoadReq req2;
    GroupEntry *e;
    int task;
    int n;

    initSlowManager();
    for (;;) {
        while (!CheckCamFinalizerReady() || !D_0017A870)
            scrRun();
        if (D_0017A868 && D_0017A86C) {
            for (;;) {
                e = isysGroupForFirst(B_00188730, 0);
                n = 0;
                task = 0;
                while (e) {
                    task = e->task;
                    e = isysGroupForNext(e, 0);
                    n++;
                }
                if (task)
                    isysGroupForExit(task, 0);
                if (n <= 0)
                    break;
                func_000283D8(&req, B_00188668);
                scrRun();
            }
            func_000283D8(&req, B_00188668);
            func_0002ABB0(B_00188668, &req, func_0002D480, func_0002D4F8, 1);
            func_0002AEA8(&req2, B_00188650);
            func_0002ABB0(B_00188650, &req2, func_00027588, func_00027778, 0);
        }
        scrRun();
    }
}
