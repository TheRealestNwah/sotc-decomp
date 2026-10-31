typedef struct {
    int id;
} Key;

typedef struct {
    char pad0[0xBC];
    int id;
} Target;

typedef struct {
    char pad0[0x1C];
    Key *key;
    char pad20[0xCC - 0x20];
    Target *target;
} Obj;

static int func_001038C8(Obj *o)
{
    Target *t = o->target;
    Key *k = o->key;

    return k->id == t->id;
}
