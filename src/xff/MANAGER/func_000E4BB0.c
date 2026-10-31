typedef struct { char pad0[8]; void (*unload)(void *); } SheetOps;
typedef struct { char pad0[0x38]; SheetOps *ops; } SheetType;
typedef struct {
    char pad0[0x38];
    void *data;
    SheetType *type;
    char pad40[4];
    unsigned int flags;
} Sheet;

extern void sheetFileUnloadCallBack(Sheet *);

static void func_000E4BB0(Sheet *s)
{
    void (*fn)(void *);

    if (s->flags & 0x3FF00000)
        return;
    fn = s->type->ops->unload;
    if (fn)
        fn(s->data);
    if (s->flags & 0x3FF00000)
        return;
    sheetFileUnloadCallBack(s);
}
