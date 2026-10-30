extern unsigned char *B_000C5C0C;
typedef struct {
    char pad0[0x314 - 0x2B0];
    signed char nrpn[3];
    char pad[0x70 - (0x317 - 0x2B0)];
} ModChannel;
typedef struct {
    char pad0[0x2B0];
    ModChannel ch[16];
} ModState;
extern ModState *B_000C5C10;
extern int B_000C5C08;
extern int Sg2DspEffectSetType(int i, int v);
extern short Sg2DspEffectSetDepth(int arg0, short arg1);
extern int Sg2DspEffectSetDelay(int i, int v);
extern int Sg2DspEffectSetFeedBack(int i, int v);
extern int Sg2DspEffectChange(int i);
extern int Sg2ModSetParam(int mod, int param, int a, int b);

static void func_00024748(void)
{
    unsigned char *ev = B_000C5C0C;
    ModState *st = B_000C5C10;
    int ch = ev[0] & 0xF;
    signed char *nrpn;

    st->ch[ch].nrpn[2] = ev[2];
    nrpn = (signed char *)st + ch * 0x70 + 0x314;
    switch (nrpn[0]) {
    case 0:
        switch (nrpn[1]) {
        case 0:
            Sg2DspEffectSetType(0, nrpn[2]);
            break;
        case 1:
            Sg2DspEffectSetDepth(0, nrpn[2]);
            break;
        case 2:
            Sg2DspEffectSetDelay(0, nrpn[2]);
            break;
        case 3:
            Sg2DspEffectSetFeedBack(0, nrpn[2]);
            break;
        case 0x7F:
            Sg2DspEffectChange(0);
            break;
        }
        break;
    case 1:
        switch (nrpn[1]) {
        case 0:
            Sg2DspEffectSetType(1, nrpn[2]);
            break;
        case 1:
            Sg2DspEffectSetDepth(1, nrpn[2]);
            break;
        case 2:
            Sg2DspEffectSetDelay(1, nrpn[2]);
            break;
        case 3:
            Sg2DspEffectSetFeedBack(1, nrpn[2]);
            break;
        case 0x7F:
            Sg2DspEffectChange(1);
            break;
        }
        break;
    case 2:
        if (nrpn[1] == 0) {
            Sg2ModSetParam(B_000C5C08, 0x800, nrpn[2], 0);
        }
        break;
    }
}
