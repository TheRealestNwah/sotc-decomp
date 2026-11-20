typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct KPrintfContext {
    int pad[16];
} KPrintfContext;

extern unsigned char RO_0017C108[];

extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int iosInitKPrintfContext3D(float, float, float, KPrintfContext *, Vec4 *, int, int, float);
extern void kprintfContextCentering(KPrintfContext *, unsigned char *, char *);
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(Vec4 *, float, int);

static inline void ggp(Vec4 *o, void *g)
{
    GetGeometryPointerPosition(o, g);
}

void dispgpinfo(char *name, void *gp, float r, float g, float b)
{
    Vec4 pos;
    KPrintfContext ctx;
    Vec4 p;

    GetGeometryPointerPosition(&pos, gp);
    if (iosInitKPrintfContext3D(r, g, b, &ctx, &pos, 0, 1, 1.0f)) {
        kprintfContextCentering(&ctx, RO_0017C108, name);
    }
    glColor4f(r, g, b, 1.0f);
    ggp(&p, gp);
    DebugDispRadiusIndicator(&p, 0.1f, 1);
    DebugDispRadiusIndicator(&p, 0.03f, 1);
}
