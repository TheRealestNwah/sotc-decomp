typedef struct {
    unsigned int on : 1;
    unsigned int pad : 31;
    int a;
    int b;
} KeyEnt;

typedef struct {
    KeyEnt cur[256];
    int flags;
    KeyEnt hist[2][256];
    int acc;
    int idx;
} KeyState;

extern KeyState B_0014A6C0;

static int func_000CCAE8(unsigned char *msg)
{
    int i;

    for (i = 0; i < 256; i++)
        B_0014A6C0.cur[i].on = 0;
    for (i = 0; i < msg[1] - 2; i++)
        B_0014A6C0.cur[msg[4 + i]].on = 1;
    B_0014A6C0.flags = msg[2] & 0xF;
    for (i = 0; i < 256; i++)
        B_0014A6C0.hist[B_0014A6C0.idx][i].on |= B_0014A6C0.cur[i].on;
    B_0014A6C0.acc |= B_0014A6C0.flags;
    return 1;
}
