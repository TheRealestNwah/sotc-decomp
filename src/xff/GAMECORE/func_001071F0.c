typedef struct {
    char pad0[0xA0];
    int id0;
    int id1;
    int padA8;
    int id2;
    int id3;
    int id4;
    int id5;
} Slots;

typedef struct {
    char pad0[0x1C];
    int *key;
    char pad20[0xCC - 0x20];
    Slots *slots;
} Owner;

static int func_001071F0(Owner *o)
{
    Slots *s = o->slots;

    if (s->id0 == *o->key || s->id1 == *o->key || s->id2 == *o->key || s->id3 == *o->key
        || s->id4 == *o->key || s->id5 == *o->key)
        return 1;
    return 0;
}
