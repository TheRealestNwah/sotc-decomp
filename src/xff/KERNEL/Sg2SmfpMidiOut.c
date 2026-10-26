typedef struct {
    int status;
    int reserved;
    int mod;
    char pad[0x74];
} Smfp;

extern Smfp B_000E0DC0[];
extern unsigned char B_000E19E0[];
extern int B_000E21E0;

static inline void writeMidiPayload(int length, const unsigned char *data)
{
    while (length != 0) {
        B_000E19E0[B_000E21E0++] = *data++;
        length--;
    }
}

int Sg2SmfpMidiOut(int id, int length, const unsigned char *data)
{
    if (id >= 0) {
        Smfp *player;

        id <<= 7;
        player = (Smfp *)((char *)B_000E0DC0 + id);
        if (player->status == 0)
            return -1;
        B_000E19E0[B_000E21E0++] = player->mod;
        B_000E19E0[B_000E21E0++] = length;
        writeMidiPayload(length, data);
    }
    return 0;
}
