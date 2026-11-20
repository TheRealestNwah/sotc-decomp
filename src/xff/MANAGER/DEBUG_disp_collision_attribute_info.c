extern char *D_0012FDF8[];
extern char *D_0012FEE8[];
extern char *D_0012FF68[];
extern char *D_0012FFE8[];
extern char *D_00130090[];
extern char *D_001300C0[];
extern char *D_00130140[];
extern void iosSetKPrintfLocateContext(void *, float, float);
extern void kprintfContext(void *, const char *, ...);

float DEBUG_disp_collision_attribute_info(unsigned long a, void *ctx, float x, float y, float h)
{
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "BOSS   : %d  SLIP   : %d", a & 1, (a & 2) >> 1);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "GRIP   : %d  DAMAGE : %d", (a & 4) >> 2, (a & 8) >> 3);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "CAMERA : %d  EVENT  : %d", (a >> 15) & 0x3F, (a >> 21) & 0xF);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "PATH   : %d", (a & 0x2000000000000000UL) >> 61);
    y += h;
    y += h * 0.3f;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "PARTS  : %s", D_0012FDF8[(int)((a & 0x3F0) >> 4)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "MATERI : %s", D_0012FEE8[(int)((a & 0x7C00) >> 10)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "ACTION : %s", D_0012FF68[(int)((a >> 26) & 0x1F)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "ETC    : %s", D_001300C0[(int)((a & 0xF80000000UL) >> 31)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "CAM_PLACE : %s", D_0012FFE8[(int)((a & 0x3F000000000UL) >> 36)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "CAM_OPT   : %s", D_00130090[(int)((a & 0x3C0000000000UL) >> 42)]);
    y += h;
    iosSetKPrintfLocateContext(ctx, x, y);
    kprintfContext(ctx, "DP        : %s", D_00130140[(int)((a >> 47) & 0x7F)]);
    return y + h;
}
