struct PadSys {
    char unk0[0x100];
    unsigned char profile[4];
    unsigned char data[0x14];
    int state;
    int socket;
    int phase;
    char unk124[0x1C];
};

extern int scePad2GetState(int socket);
extern int scePad2GetButtonProfile(int socket, unsigned char *profile);
extern int scePad2Read(int socket, unsigned char *data);
extern struct PadSys D_0013D840[2];

void padSysTickProc(void) {
    struct PadSys *pad;
    int i;

    for (i = 0; i < 2; i++) {
        pad = &D_0013D840[i];
        pad->state = scePad2GetState(pad->socket);
        if (pad->state == 1) {
            switch (pad->phase) {
            case 0:
                scePad2GetButtonProfile(pad->socket, pad->profile);
                pad->data[1] = 0;
                pad->data[0] = 0;
                pad->data[5] = 0x7F;
                pad->data[4] = 0x7F;
                pad->data[3] = 0x7F;
                pad->data[2] = 0x7F;
                pad->phase++;
                break;
            case 1:
                scePad2Read(pad->socket, pad->data);
                pad->data[0] = pad->profile[0] & ~pad->data[0];
                pad->data[1] = pad->profile[1] & ~pad->data[1];
                if (pad->profile[2] == 0) {
                    pad->data[5] = 0x7F;
                    pad->data[4] = 0x7F;
                    pad->data[3] = 0x7F;
                    pad->data[2] = 0x7F;
                }
                break;
            }
        } else {
            pad->phase = 0;
            pad->data[1] = 0;
            pad->data[0] = 0;
            pad->data[5] = 0x7F;
            pad->data[4] = 0x7F;
            pad->data[3] = 0x7F;
            pad->data[2] = 0x7F;
        }
    }
}

