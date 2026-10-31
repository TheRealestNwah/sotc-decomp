typedef struct {
    int active;
    int b;
    int c;
} Slot;

typedef struct {
    char pad0[0x5C];
    Slot slot;
} Obj;

static void func_0004EAB0(Obj *o)
{
    Slot *s = &o->slot;

    if (s->active) {
        s->active = 0;
        s->b = 0;
        s->c = 0;
    }
}
