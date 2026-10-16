typedef struct {
    int active;
    int pad;
    unsigned long flags;
    char pad2[0x60];
} SepEnt;

extern SepEnt B_000C2910[];

/* Sets the stop bit on every active sequence of the given type. */
void sndSepStopTypeAll(int type)
{
    unsigned long stop;
    SepEnt *e = B_000C2910;
    int i;

    stop = 0x100000000UL;
    for (i = 0x1F; i >= 0; i--, e++) {
        if (e->active != 0 && ((int)(e->flags >> 34) & 7) == type) {
            e->flags |= stop;
        }
    }
}
