typedef struct PadManager {
    int f0;
    int f4;
    unsigned int trig;
    int fC;
    unsigned int rep;
} PadManager;

typedef struct KeyEnt {
    char pad[8];
    signed char c;
    char pad9[7];
} KeyEnt;

typedef struct Input {
    char pad0[8];
    void (*cb)(char *);
    char padC[8];
    char *buf;
    int pos;
    int ch;
} Input;

typedef struct Win {
    char pad0[0x1C4];
    unsigned int flags;
    char pad1C8[0x3E0 - 0x1C8];
    Input *in;
} Win;

extern PadManager padManagerData;
extern KeyEnt D_00139730[5][13];
extern int D_00139B40;
extern int D_00139B44;
extern void windowCloseRequest(Win *);

static void func_000D3890(void *a0, Win *w)
{
    Input *in = w->in;
    int found;
    int r, c;

    if (w->flags & 0x40040) {
        in->buf[in->pos] = in->ch;
        in->buf[in->pos + 1] = 0;
        windowCloseRequest(w);
        return;
    }
    if (padManagerData.rep & 0x1000) {
        if (--D_00139B44 < 0)
            D_00139B44 = 4;
    }
    if (padManagerData.rep & 0x4000) {
        if (++D_00139B44 >= 5)
            D_00139B44 = 0;
    }
    if (padManagerData.rep & 0x8000) {
        if (--D_00139B40 < 0)
            D_00139B40 = 12;
    }
    if (padManagerData.rep & 0x2000) {
        if (++D_00139B40 >= 13)
            D_00139B40 = 0;
    }
    in->ch = ((KeyEnt *)D_00139730)[D_00139B44 * 13 + D_00139B40].c;
    if (in->ch == 0x3D) {
        in->buf[in->pos] = 0;
        if (padManagerData.trig & 0x20) {
            if (in->cb != 0)
                in->cb(in->buf);
            windowCloseRequest(w);
        }
        return;
    }
    found = 0;
    if (padManagerData.trig & 0x10) {
        if (--in->pos < 0) {
            in->pos = 0;
        } else {
            for (r = 0; r < 5; r++) {
                for (c = 0; c < 13; c++) {
                    if (D_00139730[r][c].c == in->buf[in->pos]) {
                        D_00139B40 = c;
                        found = 1;
                        D_00139B44 = r;
                        in->ch = D_00139730[r][c].c;
                    }
                    if (found)
                        goto out;
                }
            }
        }
    } else if (padManagerData.trig & 0x20) {
        if (++in->pos >= 0x22)
            in->pos = 0x21;
    }
out:
    in->buf[in->pos] = in->ch;
    in->buf[in->pos + 1] = 0;
}
