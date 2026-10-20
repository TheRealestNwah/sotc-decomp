typedef struct { int status, previous, unk8, vab, mod; char pad14[60]; } Sep;
extern Sep B_000DD700[];
extern int vab_check_alive(int);
extern int vab_set_semastervol(int, int);
extern int Sg2ModSetParam(int, int, int, int);
int Sg2SepMasterVol(int vab, int volume)
{
    int i;
    Sep *sep;
    if (!vab_check_alive(vab)) {
        return -1;
    }
    vab_set_semastervol(vab, volume);
    sep = B_000DD700;
    for (i = 31; i >= 0; i--, sep++) {
        if (sep->vab == vab) {
            Sg2ModSetParam(sep->mod, 2, volume, 0);
        }
    }
    return volume;
}
