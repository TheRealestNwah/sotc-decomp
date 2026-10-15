typedef struct { int on; char pad[0x14]; int id; int closed; char pad2[0x38]; } EvBgm;
extern EvBgm B_001A5A78[];
extern void bgmStop(int, int, float);

void eventBgmAllClose(void)
{
    EvBgm *e = B_001A5A78;
    int i;
    for (i = 0; i < 2; i++, e++) {
        if (e->on != 0 && e->closed == 0) {
            bgmStop(e->id, 0, 5.0f);
            e->closed = 1;
        }
    }
}
