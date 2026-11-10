typedef struct {
    int flags;
    int data[0x74];
} Voice;
typedef struct {
    int mode;
    int flags;
    int buf[1];
} Out;
extern Voice B_000E2518[4];
extern void func_0002DD90(void *b, int n);
extern void func_0002DDB0(void *b, int n);
extern void func_0002E150(void *b, int n);
extern void func_0002E1B0(void *b, int n);
extern void func_0002E2B8(void *b, void *d, int n);
extern void func_0002E2F0(Voice *v, int n);

static void func_0002E498(Out *o, int n)
{
    int i;
    if (o->flags & 4)
        return;
    func_0002DD90(o->buf, n);
    for (i = 0; i < 4; i++) {
        if (B_000E2518[i].flags & 1) {
            func_0002E2F0(&B_000E2518[i], n);
            func_0002E2B8(o->buf, B_000E2518[i].data, n);
        }
    }
    func_0002E1B0(o->buf, n);
    if (o->mode == 0)
        func_0002E150(o->buf, n);
    func_0002DDB0(o->buf, n);
}
