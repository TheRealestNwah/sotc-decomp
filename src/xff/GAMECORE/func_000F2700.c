typedef struct {
    char p0[0x8C];
    int type;
    int kind;
    char p94[0xA8 - 0x94];
    int id;
} Sub;

typedef struct {
    char p0[0x4C];
    Sub sub;
} Obj;

static int func_000F2700(Obj *a, Obj *b)
{
    int t;

    if (b != 0) {
        Sub *x = &a->sub;
        Sub *y = &b->sub;
        t = x->type;
        if (t == y->type && x->id == y->id) {
            if (t == 1) {
                return 1;
            }
            if (x->kind == y->kind && (unsigned)(x->kind - 100) < 3) {
                if (t == 0 || t == 4 || t == 5 || t == 6) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
