typedef struct {
    int data[0x78 / 4];
} PadData;
typedef struct {
    PadData hist[30];
    char pad[0x188];
} PadPort;
typedef struct {
    char pad[0x78];
    PadPort port[2];
} PadManager;

extern PadManager padManagerData;
extern int D_00137728;
extern int D_0013772C;
extern int B_0014DC0C;
extern void iosPadRead(int port, PadData *out);
extern void WaitSema(int);
extern void SignalSema(int);

void EntryPadHistory(void)
{
    int prev = D_00137728 - 1;
    int i;

    if (prev < 0)
        prev = 29;
    for (i = 0; i < 2; i++) {
        padManagerData.port[i].hist[D_00137728] = padManagerData.port[i].hist[prev];
        iosPadRead(i, &padManagerData.port[i].hist[D_00137728]);
    }
    WaitSema(B_0014DC0C);
    D_00137728++;
    D_0013772C++;
    if (D_00137728 >= 30)
        D_00137728 = 0;
    if (D_0013772C >= 30)
        D_0013772C = 29;
    SignalSema(B_0014DC0C);
}
