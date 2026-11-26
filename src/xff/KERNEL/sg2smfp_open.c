/* Sg2 SMF player, part one: the slot release-level dump and opening a
 * Standard MIDI File (format 0) for playback on a free player slot. */

typedef struct {
    int on;
    int a;
    int mod;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    double tempo;
    double d38;
    double d40;
    double d48;
    double d50;
    double d58;
    unsigned char *p60;
    unsigned char *p64;
    char x68;
    char x69;
    char pad6A[2];
    int x6C;
    int x70;
    char pad74[0x78 - 0x74];
    double d78;
} Smfp;

extern Smfp B_000E0DC0[];
extern int B_000E11C4;
extern int Sg2RemoteGetSlotReleaseLv(int);
extern int sprintf(char *, const char *, ...);
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern double dpmul(double, double);
extern unsigned int Sg2CtrlGetTickMode(void);
extern int DIntr(void);
extern void EIntr(void);
extern int vab_check_alive(int);
extern int Sg2ModOpenBgm(int, int);

int Sg2SmfpOpenSelCore(int vab, unsigned char *data, int arg);

/* Writes the release level of all 48 slots to output, 12 per line. */
void Sg2SlotEnvTbl(char *output)
{
    char text[16];
    int slot;
    strcpy(output, "");
    for (slot = 0; slot < 48; slot++) {
        sprintf(text, "%04x ", Sg2RemoteGetSlotReleaseLv(slot));
        if ((slot + 1) % 12 == 0)
            strcat(text, "\n");
        strcat(output, text);
    }
}

/* Reads the MThd header chunk: only format 0 with one track is accepted. */
static int func_0002B830(Smfp *s)
{
    unsigned char *p = s->p60;
    int len = (p[4] << 24) | (p[5] << 16) | (p[6] << 8) | p[7];
    int format = (p[8] << 8) | p[9];
    int tracks = (p[10] << 8) | p[11];
    int division = (p[12] << 8) | p[13];

    if (len != 6) {
        return -1;
    }
    if (format != 0) {
        return -1;
    }
    if (tracks != 1) {
        return -1;
    }
    s->d38 = division;
    s->p60 = p + 14;
    return 0;
}

/* Skips the MTrk chunk header. */
static int func_0002B8F0(Smfp *s)
{
    s->p60 += 8;
    return 0;
}

int Sg2SmfpOpen(int vab, unsigned char *data, int arg)
{
    return Sg2SmfpOpenSelCore(vab, data, 2);
}

int Sg2SmfpOpenSelCore(int vab, unsigned char *data, int arg)
{
    int intr = DIntr();
    int ret;
    int idx;
    int j;
    int k;
    int m;
    Smfp *s;
    double t;

    if (vab_check_alive(vab) == 0) {
        ret = -1;
        goto end;
    }
    idx = -1;
    j = 0;
    do {
        k = (B_000E11C4 + j) & 7;
        if (B_000E0DC0[k].on == 0) {
            idx = k;
            B_000E0DC0[k].on = 1;
            B_000E0DC0[k].a = B_000E11C4++;
            break;
        }
        j++;
    } while (j < 8);
    if (idx == -1) {
        ret = -1;
        goto end;
    }
    ret = idx;
    s = &B_000E0DC0[idx];
    if (s->on != 1) {
        ret = -1;
        goto end;
    }
    s->p60 = data;
    if (func_0002B830(s) != 0) {
        ret = -1;
        goto end;
    }
    if (func_0002B8F0(s) != 0) {
        ret = -1;
        goto end;
    }
    m = Sg2ModOpenBgm(vab, arg);
    if (m == -1) {
        ret = -1;
        goto end;
    }
    s->mod = m;
    s->xC = vab;
    s->tempo = 120.0;
    s->d78 = 100.0;
    t = 1000000.0 / (60000000.0 / s->tempo) * s->d38;
    s->d40 = t / Sg2CtrlGetTickMode();
    s->d40 = dpmul(s->d40, s->d78) / 100.0;
    s->x10 = 0x7F;
    s->x14 = 0x7F;
    s->x18 = 0x40;
    s->p64 = s->p60;
    s->x1C = 0x40;
    s->x70 = 0x7F;
    s->x6C = 0;
    s->x69 = 0;
    s->d48 = 0;
end:
    if (intr)
        EIntr();
    return ret;
}
