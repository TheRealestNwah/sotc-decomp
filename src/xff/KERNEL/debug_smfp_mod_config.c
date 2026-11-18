typedef struct {
    int state;
    char pad04[0x8 - 0x4];
    int modId;
    char pad0C[0x20 - 0xC];
    int beatDen;
    int beatNum;
    int tick;
    int beat;
    double bpm;
    double tpb;
    char pad40[0x48 - 0x40];
    double clock;
    char pad50[0x58 - 0x50];
    double time;
    char pad60[0x78 - 0x60];
    double speed;
} Smfp;

extern Smfp B_000E0DC0[];
extern int D_00041520;
extern int D_00041524;
extern int D_00041528;
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern int sprintf(char *, const char *, ...);
extern void debug_mod_config(int, char *, int);

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

void debug_smfp_mod_config(int i, char *out)
{
    char buf[0x200];
    Smfp *p = &B_000E0DC0[i];
    int clock, tpb, rem;
    double t;

    strcpy(out, "");
    clock = p->clock;
    tpb = p->tpb;
    if (clock != 0)
        rem = clock % tpb;
    sprintf(buf, "[ Beat / Position ] : < %d/%d >/< %03d.%03d.%03d >\n", p->beatNum, p->beatDen, p->beat,
            p->tick, rem);
    strcat(out, buf);
    if (i >= 0 && p->clock != 0.0 && p->speed != 0.0) {
        t = p->time / 60.0;
        if (t < 0.0)
            t = 0.0;
        split(t, &D_00041520, &D_00041524, &D_00041528);
    }
    if (D_00041528 > 500)
        sprintf(buf, "[  Bpm / Now Time ] : < %07.3f >/< %02d %02d %03d >\n", p->bpm, D_00041520, D_00041524,
                D_00041528);
    else
        sprintf(buf, "[  Bpm / Now Time ] : < %07.3f >/< %02d:%02d:%03d >\n", p->bpm, D_00041520, D_00041524,
                D_00041528);
    strcat(out, buf);
    sprintf(buf, "[ Player Speed ] : %03.0f %%% \n", p->speed);
    strcat(out, buf);
    sprintf(buf, "[ Smfp/Mod Id  ] : Smfp:%d / Module:%d\n", i, p->modId);
    strcat(out, buf);
    D_00041520 = p->tick;
    if (p->state != 2)
        D_00041520 = 0;
    debug_mod_config(B_000E0DC0[i].modId, buf, D_00041520);
    strcat(out, buf);
}
