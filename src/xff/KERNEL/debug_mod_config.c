typedef struct {
    char pad00[0x68];
    int on;
    char pad6C[0x70 - 0x6C];
} ModCh;

typedef struct {
    char pad000[0x4];
    int clsid;
    char pad008[0x14 - 0x8];
    int mode;
    char pad018[0x34 - 0x18];
    int volL;
    int volR;
    int pan;
    int noteShift;
    int tune;
    char pad048[0x50 - 0x48];
    int velTable;
    int lfoTable;
    char pad058[0x264 - 0x58];
    int midiWr;
    int midiRd;
    char pad26C[0x2B0 - 0x26C];
    ModCh ch[16];
} Mod;

extern Mod B_000C5C18[];
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern int sprintf(char *, const char *, ...);

void debug_mod_config(int i, char *out, int sel)
{
    char mark[2][2] = { "#", "-" };
    char buf[0x80];
    Mod *m = &B_000C5C18[i];
    int k;

    if (i >= 0) {
        strcpy(out, "");
        strcpy(buf, "");
        sprintf(buf, "[ Midi Ch ] 0123456789ABCDEF(Hex)\n");
        strcat(buf, "            ");
        for (k = 0; k < 16; k++) {
            if (m->ch[k].on)
                strcat(buf, mark[sel % 2]);
            else
                strcat(buf, "_");
        }
        strcat(buf, "\n");
        strcat(out, buf);
        sprintf(buf, "[ SlClsid ] %08x\n", m->clsid);
        strcat(out, buf);
        if (m->mode == 1)
            strcat(out, "[  Mode   ] Bgm Play Module\n");
        else if (m->mode == 2)
            strcat(out, "[  Mode   ] Se Play Module\n");
        else if (m->mode == 3)
            strcat(out, "[  Mode   ] Adpcm Stream Module\n");
        else
            strcat(out, "[  Mode   ] Unknown\n");
        sprintf(buf, "[ MidiBuf ] Size:%04d Rd:%04d Wr:%04d\n", 0x200, m->midiRd, m->midiWr);
        strcat(out, buf);
        strcat(out, "[  Param  ]\n");
        sprintf(buf, "       MasVol_l:(%03d) Masvol_r:(%03d) MasPan :(%03d)\n", m->volL, m->volR, m->pan);
        strcat(out, buf);
        sprintf(buf, "       NoteShift :(%03d) MasTune:(%04xH)\n", m->noteShift, m->tune);
        strcat(out, buf);
        strcat(out, "[  Table  ]\n");
        if (m->velTable == 0)
            sprintf(buf, "  Velocity Table:No");
        else
            sprintf(buf, "  Velocity Table:Have");
        strcat(out, buf);
        sprintf(buf, "  Velocity Table:Have");
        sprintf(buf, "  Lfo Wave Table:%d\n", m->lfoTable + 1);
        strcat(out, buf);
    }
}
