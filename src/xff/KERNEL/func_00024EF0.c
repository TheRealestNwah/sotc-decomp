typedef struct {
    char pad0[0x2B8 - 0x2B0];
    int prog;
    char pad8[0x310 - 0x2BC];
    struct {
        char pad0[8];
        void *progchunk;
        char *splitchunk;
    } voice;
    char pad[0x70 - (0x320 - 0x2B0)];
} ModChannel;
typedef struct {
    int vab;
    char pad4[0x2B0 - 4];
    ModChannel ch[16];
} ModState;

extern unsigned char *B_000C5C0C;
extern ModState *B_000C5C10;
extern void *vab_get_progchunk(int i, unsigned int prog);
extern char *vab_get_splitchunk(char *p);

static void func_00024EF0(void)
{
    unsigned char *ev = B_000C5C0C;
    ModState *st = B_000C5C10;
    int ch = ev[0] & 0xF;
    void *prog;

    st->ch[ch].prog = ev[1];
    prog = vab_get_progchunk(st->vab, ev[1]);
    B_000C5C10->ch[ch].voice.progchunk = prog;
    B_000C5C10->ch[ch].voice.splitchunk = vab_get_splitchunk(prog);
}
