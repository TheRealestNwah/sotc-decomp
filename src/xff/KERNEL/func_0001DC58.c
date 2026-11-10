typedef unsigned long u64;

typedef struct {
    short unk0;
    short unk2;
    int id;
    union {
        struct {
            u64 lo : 34;
            u64 mode : 3;
        } b;
        int w;
    } f;
    char pad10[0x10];
    float cur;
    float target;
    short volTarget;
    short vol;
    short unk2C;
    short unk2E;
    short unk30;
} SepVoice;

extern int D_00040FAC;
extern int Sg2SepSetParam(unsigned int id, int selector, int value, int extra);

#ifdef NONMATCHING
/* Parked: mode-check branch shape and volume-store conversions differ. */
void func_0001DC58(SepVoice *v)
{
    int id = v->id;
    float t;
    int n;
    short vol;
    int d;

    if (D_00040FAC == 0 || v->f.b.mode == 1) {
        t = v->volTarget;
    } else {
        t = 0.0f;
    }
    vol = v->vol;
    if (vol != t) {
        d = vol - t;
        if (vol >= 0) {
            if (d > 0) {
                if (d >= 10) {
                    n = vol - 10;
                    goto conv;
                }
            } else if (d < -9) {
                n = vol + 10;
                goto conv;
            }
        }
        v->vol = t;
        goto done;
    conv:
        v->vol = (float)n;
    done:
        Sg2SepSetParam(id, 2, v->vol, 0);
    }
    if (v->cur != v->target) {
        float cur = v->cur;
        float tg = v->target;
        float diff = cur - tg;
        if (cur < 0.0f) {
            v->cur = tg;
        } else if (diff > 0.0f) {
            if (diff < 2.5) {
                v->cur = tg;
            } else {
                v->cur = cur - 2.5;
            }
        } else if (diff > -2.5) {
            v->cur = tg;
        } else {
            v->cur = cur + 2.5;
        }
        Sg2SepSetParam(id, 4, (int)v->cur, 0);
    }
    if (v->f.w & 4) {
        Sg2SepSetParam(id, 0x40, v->unk2C, 0);
    }
    if (v->f.w & 8) {
        Sg2SepSetParam(id, 0x80, v->unk2E, v->unk30);
    }
    v->f.w = 0;
}
#endif
