typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x134];
    /* The char member lets the stores below alias the pointer, so it is
       reloaded for the second copy, as in the original. */
    union {
        u_long128 *pos;
        char alias;
    } pos;
} PerceptionObj;

typedef struct {
    u_long128 last[2];
    char pad[0x2C];
    PerceptionObj *obj;
} PerceptionWork;

void forceRenewLastPosPerceptionWork(void *unused, PerceptionWork *work)
{
    PerceptionObj *obj = work->obj;

    work->last[0] = *obj->pos.pos;
    work->last[1] = *obj->pos.pos;
}
