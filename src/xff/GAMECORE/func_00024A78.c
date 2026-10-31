typedef struct Stage {
    int a;
    int b;
    int c;
    char pC[0xC];
    struct Stage *next;
} Stage;
typedef struct {
    int done;
    int step;
} Req;
extern Stage *D_0017A3D4;
extern int func_0001EC38(Stage *);
extern void func_0001FA68(int, int, int);
extern void scrRun(void);

static void func_00024A78(Req *req)
{
    Stage *s = D_0017A3D4;
    int n = 0;

    while (s != 0) {
        if (func_0001EC38(s) != 0) {
            n++;
            func_0001FA68(s->c, s->a, s->b);
            if (n % req->step == 0) {
                scrRun();
            }
        }
        s = s->next;
    }
    req->done = 0;
}
