typedef struct {
    int width;
    int height;
    int dispW;
    int dispH;
    char pad10[0x78];
    char *root;
} GsMode;

typedef struct {
    char pad0[0x1C];
    char *dc;
} DrawContextSet;

extern GsMode B_00065550;
extern char rootPtn[];
extern DrawContextSet *iosCreateDC(void *, int);
extern void iosSetDCParam(void *, int, int, int, int);
extern void iosSetDCClearParam(void *, int, int, int, int, int);
extern void iosSetDCViewPort(void *, int, int, int, int);

void iosSetRootContext(void)
{
    char *root;
    char *dc;
    int i;

    root = iosCreateDC(rootPtn, 2)->dc;
    dc = root;
    for (i = 1; i >= 0; i--) {
        iosSetDCParam(dc,
                      ((B_00065550.width * B_00065550.height) >> 11) +
                          ((B_00065550.dispW * B_00065550.dispH) >> 11),
                      (B_00065550.width * B_00065550.height) >> 11,
                      B_00065550.dispW, B_00065550.dispH);
        iosSetDCClearParam(dc, 1, 0, 0, 0, 0x80);
        iosSetDCViewPort(dc, 0, 0, B_00065550.dispW, B_00065550.dispH);
        dc += 0x190;
    }
    B_00065550.root = root;
}
