#include "kernel/sg2sep.h"

extern int D_00041470;
extern int D_00041474;
extern int D_00041478;
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern int sprintf(char *, const char *, ...);

static inline void split(double t, int *m, int *s, int *ms)
{
    int v;
    v = t / 60.0;
    if (v < 0)
        v = 0;
    *m = v;
    v = t - v * 60;
    if (v < 0)
        v = 0;
    *s = v;
    *ms = (t - (int)t) * 1000.0;
    if (*ms < 0)
        *ms = 0;
}

void debug_sep_config(int i, char *out)
{
    char buf[0x200];
    Sep *sep = &B_000DD700[i];
    double pos, t;
    int v;

    strcpy(out, "");
    if (i >= 0) {
        pos = sep->time.d;
        if (pos != 0.0) {
            t = pos / 480.0;
            if (t < 0.0)
                t = 0.0;
            split(t, &D_00041470, &D_00041474, &D_00041478);
        }
    }
    if (D_00041478 > 500)
        sprintf(buf, "[ Seq Position ] : %02d %02d %03d\n", D_00041470, D_00041474, D_00041478);
    else
        sprintf(buf, "[ Seq Position ] : %02d:%02d:%03d\n", D_00041470, D_00041474, D_00041478);
    strcat(out, buf);
}
