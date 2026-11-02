extern const char RO_0013B260[];
extern const char RO_0013C780[];
extern int DebugGetParentCharColAttr(long *, void *);
extern void iosSetKPrintfLocateContext(void *, float, float);
extern char *GetLayoutClass(void *);
extern void *GetLayoutParentObj(void *);
extern void kprintfContext(void *, const char *, ...);

float DEBUG_disp_collision_name(void *obj, void *ctx, float x, float y, float lineHeight)
{
    long attr = 0;

    if (DebugGetParentCharColAttr(&attr, obj) == 1) {
        void *parent;
        const char *dflt;
        const char *name;

        iosSetKPrintfLocateContext(ctx, x, y);
        dflt = RO_0013C780;
        parent = GetLayoutParentObj(GetLayoutClass(obj));
        name = dflt;
        if (parent != 0)
            name = *(const char **)(GetLayoutClass(parent) + 0x130);
        kprintfContext(ctx, RO_0013B260, name);
        y += lineHeight * 1.2f;
    }
    return y;
}
