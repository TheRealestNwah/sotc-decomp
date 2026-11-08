typedef struct {
    char pad0[0x130];
    char *name;
} LayoutClass;

extern int *GetGlDebugSw(void);
extern void iosInitKPrintfContext(void *, int, int, float, float, float, float, float, float);
extern void iosSetKPrintfColorContext(void *, int, float, float, float, float);
extern void kprintfContext(void *, const char *, ...);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern LayoutClass *GetLayoutClass(void *);
extern char gcGlobalVar[];
extern int D_00179A54;
extern const char RO_0017C638[];
extern const char RO_0017C648[];

#ifdef NONMATCHING
/* Parked: 91 words differ (gcc hoists the 1.0f color constants into $f20; original keeps &D_00179A54 and the format string in s5/s7) */
static void *func_00004F78(void)
{
    char ctx[0x40];
    int count = 0;
    void *sel = 0;
    void **link;
    void *obj;
    LayoutClass *cls;

    if (*GetGlDebugSw() != 0) {
        iosInitKPrintfContext(ctx, 0, 0, 100.0f, -120.0f, 1.0f, 0.5f, 0.0f, 1.0f);
        kprintfContext(ctx, RO_0017C648);
    }
    obj = 0;
    for (link = isysGroupForFirst(gcGlobalVar + 0x2B8, 0); link != 0; link = isysGroupForNext(link, 0)) {
        obj = *link;
        count++;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    if (D_00179A54 >= count) {
        D_00179A54 = 0;
    }
    count = 0;
    obj = 0;
    for (link = isysGroupForFirst(gcGlobalVar + 0x2B8, 0); link != 0; link = isysGroupForNext(link, 0)) {
        obj = *link;
        cls = GetLayoutClass(obj);
        if (count == D_00179A54) {
            iosSetKPrintfColorContext(ctx, 0, 1.0f, 1.0f, 1.0f, 1.0f);
            kprintfContext(ctx, RO_0017C638, cls->name);
        }
        if (count == D_00179A54) {
            sel = obj;
        }
        count++;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    return sel;
}
#endif
