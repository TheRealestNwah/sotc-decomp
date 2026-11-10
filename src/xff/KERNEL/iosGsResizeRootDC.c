typedef struct {
    int w;
    int sx;
    int h;
    int sy;
    char pad10[0x88 - 0x10];
    char *dc;
} GsRoot;

extern GsRoot B_00065550;
extern volatile int D_00040B40[4];
extern void iosSetDCParam(void *dc, int a, int b, int c);
extern void iosSetDCClearParam(void *dc, int on, int r, int g, int b, int a);
extern void iosSetDCViewPort(void *dc, int x, int y, int w, int h);

void iosGsResizeRootDC(void)
{
    GsRoot *root = &B_00065550;
    volatile int *clear = D_00040B40;
    int off = 0;
    int i;

    for (i = 1; i >= 0; i--) {
        int h = root->h;
        int x, y;

        { register int sy __asm__("$8") = root->sy; /* pinned to match the original's $t0 */
          y = h * sy >> 11; }
        x = root->w * root->sx >> 11;
        iosSetDCParam(root->dc + off, x + y, x, h);
        iosSetDCClearParam(root->dc + off, 1, clear[0], clear[1], clear[2], clear[3]);
        iosSetDCViewPort(root->dc + off, 0, 0, root->h, root->sy);
        off += 0x190;
    }
}
