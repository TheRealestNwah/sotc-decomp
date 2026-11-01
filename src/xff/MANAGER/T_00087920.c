typedef struct {
    void *obj;
} SysGroup;

typedef void (*Hook)(void *, void *);

extern char *GetScriptClass(void *);
extern SysGroup *isysGroupForFirst(void *, int);
extern SysGroup *isysGroupForNext(SysGroup *, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);

static void T_00087920(void *o)
{
    char *s = GetScriptClass(o);
    char *grp;
    SysGroup *g;
    void *last;

    if (*(Hook *)(s + 0x54) != 0) {
        (*(Hook *)(s + 0x54))(o, *(void **)(s + 0x58));
    }
    if (*(Hook *)(s + 0x5C) != 0) {
        (*(Hook *)(s + 0x5C))(o, *(void **)(s + 0x60));
    }
    grp = s + 0x30;
    last = 0;
    g = isysGroupForFirst(grp, 0);
    while (g != 0) {
        last = g->obj;
        isysRequestDeleteObj(last);
        g = isysGroupForNext(g, 0);
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    isysDeleteGroupAllObj(grp);
}
