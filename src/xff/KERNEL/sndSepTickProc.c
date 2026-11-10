#ifdef NONMATCHING
/* Parked: 1 word differs (at 0xAC the original has movz v0,$s1,v1; this has
   movz v0,$zero,v1 for the sg2err(x) result). */
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
extern void func_0001DC58(SepEntry *);
extern SepEntry B_000C2910[32];

static inline int sg2err(int x) { if (x < 0) return x; return 0; }

void sndSepTickProc(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        SepEntry *e = &B_000C2910[i];
        int notify = 0;
        switch (e->state) {
        case 0:
            break;
        case 1:
            if (e->prepare(e) != 0
                || sg2err(e->handle = Sg2SepPlay(e->data->id, e->a, e->b, 0)) != 0) {
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
                func_0001DC58(e);
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
#endif
