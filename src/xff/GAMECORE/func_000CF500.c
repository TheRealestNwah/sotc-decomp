extern char gcGlobalVar[];
extern unsigned char padManagerData[];
extern int SCRGetFirstObj(void *);
extern char *GetLayoutClass(int);
extern void getPosOnMap(void *, float *, float *);

#define W(type, o) (*(type *)(w + (o)))

static void func_000CF500(void *menu, int unused, char *w)
{
    char *base = gcGlobalVar + 0x2B0;
    char *cls;
    int obj;
    float s;
    float zoom, sx, sy, d;

    obj = SCRGetFirstObj(base);
    s = W(float, 0x18);
    if (obj == 0)
        return;
    cls = GetLayoutClass(obj);
    if (cls == 0)
        return;
    getPosOnMap(*(void **)(cls + 0x134), &W(float, 0x28), &W(float, 0x30));
    W(float, 0x2C) = *(float *)(*(char **)(cls + 0x134) + 4);
    if (W(int, 0x1C) == 3) {
        if (s > 1.3f)
            s += (1.3f - s) * *(float *)(base - 0x140) * 30.0f * 0.3f;
        if (s <= 1.3009999f) {
            s = 1.3f;
            W(int, 0x1C) = 0;
        }
    } else if (W(int, 0x1C) == 2) {
        if (s > 1.3f)
            s += (1.3f - s) * *(float *)(base - 0x140) * 30.0f * 0.6f;
        if (s <= 1.3009999f) {
            s = 1.3f;
            W(int, 0x1C) = 0;
        }
    } else if (W(int, 0x1C) == 1) {
        if (s < 2.25f)
            s += (2.25f - s) * *(float *)(base - 0x140) * 30.0f * 0.6f;
        if (s >= 2.249f) {
            s = 2.25f;
            W(int, 0x1C) = 0;
        }
    } else {
        if (W(int, 0) == 3 || W(int, 0) == 4) {
            zoom = 0.0f;
            d = padManagerData[0x57] / 127.5f - 1.0f;
            sx = 2.0f * (padManagerData[0x54] / 127.5f - 1.0f);
            sy = 2.0f * (padManagerData[0x55] / 127.5f - 1.0f);
            if (d < 0.0f ? d < -0.6f : d > 0.6f)
                zoom -= d;
            if (sx < 0.0f ? sx < -0.6f : sx > 0.6f)
                W(float, 0x50) -= sx;
            if (sy < 0.0f ? sy < -0.6f : sy > 0.6f)
                W(float, 0x54) -= sy;
            if (zoom > 0.1f) {
                if (s < 2.25f)
                    s += (2.25f - s) * zoom * 0.1f;
            } else if (zoom < -0.1f) {
                if (s > 1.3f)
                    s -= (1.3f - s) * zoom * 0.1f;
            }
            if (s < 1.3f)
                s = 1.3f;
            if (s > 2.25f)
                s = 2.25f;
        }
    }
    W(float, 0x18) = s;
}
