typedef struct { int status, previous; char pad8[8]; int mod; char pad14[60]; } Sep;
extern Sep B_000DD700[];
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2ModSetParam(int, int, int, int);
int Sg2SepPause(unsigned int id, int mode)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if ((unsigned int)(sep->status - 1) < 2) {
            enabled = DIntr();
            sep->previous = sep->status;
            Sg2ModSetParam(B_000DD700[id].mod, 0x80, 1, 0);
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, mode, 0);
            if (mode != 0) {
                sep->status = 3;
            } else {
                sep->status = 4;
            }
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}


int Sg2SepCont(unsigned int id)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if ((unsigned int)(sep->status - 3) < 2) {
            enabled = DIntr();
            Sg2ModSetParam(B_000DD700[id].mod, 0x80, 0, 0);
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 0, 0);
            sep->status = sep->previous;
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}
