#ifdef NONMATCHING
/* Parked: 11 words differ (a2=0 argument setup order; the original recomputes sp+0x50 for the second GetGeometryPointerPosition). */
typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct KPrintfContext {
    int pad[16];
} KPrintfContext;

extern unsigned char RO_0017C108[];

extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int iosInitKPrintfContext3D(KPrintfContext *, Vec4 *, int, int, float, float, float, float);
extern void kprintfContextCentering(KPrintfContext *, unsigned char *, char *);
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(Vec4 *, int, float);

void dispgpinfo(char *name, void *gp, float r, float g, float b)
{
    Vec4 pos;
    KPrintfContext ctx;
    Vec4 p;

    GetGeometryPointerPosition(&pos, gp);
    if (iosInitKPrintfContext3D(&ctx, &pos, 0, 1, r, g, b, 1.0f)) {
        kprintfContextCentering(&ctx, RO_0017C108, name);
    }
    glColor4f(r, g, b, 1.0f);
    GetGeometryPointerPosition(&p, gp);
    DebugDispRadiusIndicator(&p, 1, 0.1f);
    DebugDispRadiusIndicator(&p, 1, 0.03f);
}
#endif
