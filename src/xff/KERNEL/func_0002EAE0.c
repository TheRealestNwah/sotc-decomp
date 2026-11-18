typedef struct { int time; int x4; int type; float x; float y; } Node;
typedef struct {
    int active; int flags; int type; float tx; float ty; float dx; float dy;
    int x1C; int x20; int left; Node *node; char pad2C[0x34 - 0x2C];
    int iir0[(0x60 - 0x34) / 4]; float cy; float cx; char pad68[0x7C - 0x68];
    int iir1[(0xC4 - 0x7C) / 4];
} Ramp;
extern char B_000E251C[];
extern char B_000E2368[];
extern int Sg2CtrlGetTickMode(void);
extern void IirParam(void *p, float freq, float gain, int type);
static void func_0002E8D8(Node *node, int ch, int a2, int a3);

static void func_0002EAE0(void)
{
    int ch;
    int i;
    Ramp *r;
    int type;
    float cx, cy;

    for (ch = 0; ch < 5; ch++) {
        char *base;
        if (ch >= 4) base = B_000E2368;
        else base = B_000E251C + ch * 0x1D4;
        r = (Ramp *)(base + 0x14);
        for (i = 0; i < 2; i++, r++) {
            if (r->active && r->flags) {
                type = r->iir0[0];
                if (r->flags & 4) {
                    r->flags &= ~4;
                    type = r->type;
                }
                cx = r->cx;
                if (r->flags & 1) {
                    float d = r->dx;
                    cx += d;
                    if ((d > 0.0f && r->tx < cx) || (d < 0.0f && cx < r->tx)) {
                        cx = r->tx;
                        r->flags &= ~1;
                    }
                }
                cy = r->cy;
                if (r->flags & 2) {
                    float d = r->dy;
                    cy += d;
                    if ((d >= 0.0f && r->ty <= cy) || (d < 0.0f && cy < r->ty)) {
                        cy = r->ty;
                        r->flags &= ~2;
                    }
                }
                IirParam(r->iir0, cx, cy, type);
                IirParam(r->iir1, cx, cy, type);
            }
            if (i == 0 && r->node) {
                if (r->left != 0x7FFFFFFF) {
                    r->left -= 1000 / Sg2CtrlGetTickMode();
                    if (r->left < 0) {
                        r->node++;
                        func_0002E8D8(r->node, ch, r->x1C, r->x20);
                    }
                } else {
                    r->node = 0;
                }
            }
        }
    }
}
