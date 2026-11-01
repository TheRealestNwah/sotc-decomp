typedef struct { char pad0[8]; unsigned int flags; } Info;
typedef struct Obj { char pad0[0x40]; void (*fn)(void *); Info *info; } Obj;
typedef struct { char pad0[0x44]; Info *info; Obj *obj; } Self;

static void func_000DDDE0(Self *s)
{
    Obj *o = s->obj;

    if (!((s->info->flags >> 12) & 1)) {
        if (o->fn != 0)
            o->fn(o->info);
    }
}
