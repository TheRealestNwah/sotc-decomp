typedef struct {
    int a;
    int b;
    int c;
    int d;
} Sg2SlotQ;

extern int B_000DE360;
extern Sg2SlotQ B_000DE370[][14];

#ifdef NONMATCHING
/* Parked: 21 words differ (field address computation and store order) */
void Sg2SlotBlock(int owner, int slot)
{
    int seq = B_000DE360++;

    B_000DE370[slot][0].a = 0;
    B_000DE370[slot][0].b = owner;
    B_000DE370[slot][1].c = -1;
    B_000DE370[slot][1].b = -1;
    B_000DE370[slot][0].d = -1;
    B_000DE370[slot][0].c = seq;
}
#endif
