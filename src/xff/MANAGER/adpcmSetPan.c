typedef struct { float pan; char pad[0x55C]; } Adp;
extern Adp B_0014E900[];

void adpcmSetPan(int i, float f)
{
    B_0014E900[i].pan = f;
}
