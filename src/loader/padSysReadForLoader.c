struct PadSys {
    char unk0[0x104];
    unsigned char data[0x18];
    int socket;
    char unk120[0x20];
};

extern int scePad2Read(int socket, unsigned char *data);
extern struct PadSys D_0013D840[];

int padSysReadForLoader(void) {
    struct PadSys *pad = &D_0013D840[0];
    unsigned char *data = pad->data;

    if (scePad2Read(pad->socket, data) < 0) {
        return 0;
    }
    return ((data[0] << 8) | pad->data[1]) ^ 0xFFFF;
}
