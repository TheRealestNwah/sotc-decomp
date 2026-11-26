#include "kernel/sg2sep.h"
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
