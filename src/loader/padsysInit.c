struct PadSys {
    char unk0[0x11C];
    int socket;
    int unk120;
    char unk124[0x1C];
};

extern int scePad2Init(int mode);
extern int scePad2CreateSocket(int *param, void *buf);
extern struct PadSys D_0013D840[2];

void padsysInit(void) {
    struct PadSys *pad;
    int param[8];
    int i;

    scePad2Init(0);
    pad = D_0013D840;
    for (i = 0; i < 2; i++, pad++) {
        param[1] = i != 0;
        param[0] = 2;
        param[2] = 0;
        pad->socket = scePad2CreateSocket(param, pad);
        pad->unk120 = 0;
    }
}
