typedef struct { char pad[0x48]; char *tick; char rest[0x24]; } Slot;
extern Slot B_000C2910[];
extern const char RO_00044900[];
extern void iosJumpRecoverPoint(const char *);
void sndSepInitTickParam(char *data, int count, int stride)
{
    int i;
    char *current;
    if (count != 32)
        iosJumpRecoverPoint(RO_00044900);
    current = data;
    for (i = 0; i < 32; i++, current += stride) {
        B_000C2910[i].tick = current;
    }
}
