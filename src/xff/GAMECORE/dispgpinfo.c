#ifdef NONMATCHING
typedef struct {
    char pad0[0x40];
} KPrintfContext3D;

extern void GetGeometryPointerPosition(float *, int);
extern int iosInitKPrintfContext3D(KPrintfContext3D *, float *, int, int, float, float, float, float);
extern void kprintfContextCentering(KPrintfContext3D *, const char *, int);
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(float *, int, float);

void dispgpinfo(int name, int gp, float r, float g, float b)
{
    KPrintfContext3D ctx;
    float pos[4];
    float pos2[4];

    GetGeometryPointerPosition(pos, gp);
    if (iosInitKPrintfContext3D(&ctx, pos, 0, 1, r, g, b, 1.0f) != 0) {
        kprintfContextCentering(&ctx, "%s\n", name);
    }
    glColor4f(r, g, b, 1.0f);
    GetGeometryPointerPosition(pos2, gp);
    DebugDispRadiusIndicator(pos2, 1, 0.1f);
    DebugDispRadiusIndicator(pos2, 1, 0.03f);
}
#endif
