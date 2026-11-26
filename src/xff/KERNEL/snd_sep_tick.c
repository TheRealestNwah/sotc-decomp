extern int D_00040FA4;

void isysDebugSetSubThreadSleepProtection(int arg0)
{
    D_00040FA4 = arg0;
}

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
        u64 d;
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

static void func_0001DC58(SepVoice *v)
{
    int id = v->id;
    float t;
    int n;
    short vol;
    int d;

    if (D_00040FAC != 0 && ((v->f.d >> 34) & 7) != 1) {
        t = 0.0f;
        vol = v->vol;
    } else {
        t = v->volTarget;
        __asm__ __volatile__(""); /* keeps the vol load after the volTarget conversion */
        vol = v->vol;
    }
    if (vol != t) {
        d = vol - t;
        if (vol < 0) {
            v->vol = t;
        } else if (d > 0) {
            if (d < 10) {
                v->vol = t;
            } else {
                v->vol = (float)(vol - 10);
            }
        } else if (d < -9) {
            v->vol = (float)(vol + 10);
        } else {
            v->vol = t;
        }
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

typedef struct SepData { int pad0; int id; } SepData;
typedef struct SepEntry SepEntry;
struct SepEntry {
    int state;
    int handle;
    long flags;
    SepData *data;
    short a;
    short b;
    char pad18[0x34 - 0x18];
    int (*prepare)(SepEntry *);
    int (*tick)(SepEntry *);
    int pad3C;
    void (*done)(SepEntry *);
    char pad44[0x70 - 0x44];
};

extern int Sg2SepPlay(int, int, int, int);
extern int Sg2SepStatus(int);
extern void Sg2SepStop(int);
extern void Sg2SepStopSndOff(int);

extern SepEntry B_000C2910[32];

void sndSepTickProc(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        SepEntry *e = &B_000C2910[i];
        int notify = 0;
        int err;
        switch (e->state) {
        case 0:
            break;
        case 1:
            if (e->prepare(e) != 0
                || (err = notify,
                    (e->handle = Sg2SepPlay(e->data->id, e->a, e->b, 0)) < 0 && (err = e->handle),
                    err != 0)) {
                if (e->done) {
                    e->done(e);
                }
                e->state = 0;
            } else {
                e->state = 2;
                notify = 1;
            }
        case 2:
            if (Sg2SepStatus(e->handle) == 0) {
            finish:
                if (e->done) {
                    e->done(e);
                }
                e->state = 0;
            } else if ((int)(e->flags >> 32) & 1) {
                Sg2SepStop(e->handle);
                e->tick = 0;
            } else if ((int)((unsigned long)e->flags >> 33) & 1) {
                Sg2SepStopSndOff(e->handle);
                e->state = 3;
            } else if (e->tick) {
                switch (e->tick(e)) {
                case 0:
                    notify = 1;
                    break;
                case 1:
                    Sg2SepStop(e->handle);
                    e->tick = 0;
                    break;
                case 2:
                    Sg2SepStop(e->handle);
                    e->tick = 0;
                    break;
                case 3:
                    e->tick = 0;
                    break;
                }
            }
            if (notify) {
                func_0001DC58((SepVoice *)e);
            }
            break;
        case 3:
            if ((int)(e->flags >> 32) & 1) {
                e->tick = 0;
                goto finish;
            } else if (!((int)((unsigned long)e->flags >> 33) & 1)) {
                e->state = 1;
            }
            break;
        }
    }
}
