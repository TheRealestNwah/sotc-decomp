typedef struct {
    char pad[0x190];
} DC;
typedef struct {
    char pad0[0x1C];
    DC *dc;
} WinRes;
typedef struct {
    char pad0[0x1C0];
    unsigned int flags;
    char pad1C4[0xA0];
    float x;
    float y;
    float w;
    float h;
} Win;
typedef struct {
    char pad0[4];
    Win *win;
    WinRes *res;
} WinObj;
typedef struct {
    char pad0[0xB4];
    WinObj *obj;
} Obj;

extern int B_0014E888[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDrawBufferAddressFBP(void);
extern int getZBufferAddressFBP(void);
extern void iosSetDCParam(DC *, int, int, int, int);
extern void iosSetDCViewPortCenter(DC *, int, int, int, int, int, int);

void windowReInit(void)
{
    int i;
    int sw;
    int sh;

    sw = getDrawScreenWidth();
    sh = getDrawScreenHeight();

    for (i = 0; i < 2; i++) {
        void **g;
        Obj *last = 0;

        for (g = isysGroupForFirst(&B_0014E888[i], 0); g != 0; g = isysGroupForNext(g, 0)) {
            WinObj *wo;
            int j;

            last = *g;
            wo = last->obj;
            for (j = 0; j < 2; j++) {
                Win *win;
                DC *dc;
                int fbp, zbp;
                int w, h;
                int x, y, ww, wh;
                int cx, cy;

                fbp = getDrawBufferAddressFBP();
                zbp = getZBufferAddressFBP();
                iosSetDCParam(&wo->res->dc[j], fbp, zbp, sw, sh);
                dc = (DC *)(i * 0x190 + (int)wo->res->dc);
                win = wo->win;
                w = getDrawScreenWidth();
                h = getDrawScreenHeight();
                x = (int)(win->x + (float)(w >> 1));
                y = (int)(win->y + (float)(h >> 1));
                ww = (int)win->w;
                wh = (int)win->h;
                cx = -x - ww / 2;
                cy = -y - wh / 2;
                if (x < 0) {
                    ww += x;
                    x = 0;
                } else if (w - 1 < x) {
                    x = w - 1;
                }
                if (y < 0) {
                    wh += y;
                    y = 0;
                } else if (h - 1 < y) {
                    y = h - 1;
                }
                if (w - 1 < x + ww)
                    ww = w - x - 1;
                if (h - 1 < y + wh)
                    wh = h - y - 1;
                iosSetDCViewPortCenter(dc, x, y, ww, (win->flags & 1) ? 0 : wh, cx, cy);
            }
        }
        if (last != 0)
            isysGroupForExit(last, 0);
    }
}
