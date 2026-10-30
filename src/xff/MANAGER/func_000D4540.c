extern void iosFree(void *p);

typedef struct Res {
    char pad0[0xC];
    void *data;
    char pad10[8];
    void (*release)(void *, struct Res *);
} Res;

static void func_000D4540(void *owner, Res *res)
{
    if (res->release != 0) {
        res->release(owner, res);
    }
    iosFree(res->data);
}
