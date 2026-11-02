struct PadSys {
    char unk0[0x104];
    unsigned char data[0x18];
    int socket;
    char unk120[0x20];
};

extern int sceVibSetActParam(int socket, int profile_size, unsigned char *profile, int data_size, unsigned char *data);

int padSysVibSetAcrParam(struct PadSys *pad, unsigned char *param) {
    unsigned char data[2];
    unsigned char profile[1];

    data[0] = (param[0] & 1) | ((param[1] & 0x7F) << 1);
    data[1] = (param[1] & 0x80) >> 7;
    profile[0] = 3;
    return sceVibSetActParam(pad->socket, 1, profile, 2, data);
}
