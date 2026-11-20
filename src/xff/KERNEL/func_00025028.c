extern unsigned char *B_000C5C0C;
extern int *B_000C5C10;
extern int B_000C5C08;
extern int Sg2ModSetParam(int mod, int param, int a, int b);
extern void all_soundoff(int port);
extern void all_keyoff(int port);
extern unsigned int Sg2CtrlGetTickMode(void);
extern int Sg2SlotFindVabChNote(int *buf, int vab, int ch, int note);
extern int Sg2SlotFindSlotClassChNote(int *buf, int cls, int ch, int note);
extern int Sg2SlotGetPan(int slot);
extern int Sg2SlotGetVol(int slot);
extern void Sg2SlotSetTimePanParam(int slot, float time, float target);
extern void Sg2SlotSetTimeVolParam(int slot, float time, float target);
extern void Sg2SlotSetTimePitchParam(int slot, float time, float target);
extern void Sg2SlotSetLfoPitchDepth(int slot, int value);
extern void Sg2SlotSetLfoPitchSpeed(int slot, int value);

#ifdef NONMATCHING
/* 2 words differ: th * 4 is computed into a0 instead of s2 */
static void func_00025028(void)
{
    int buf[48];
    int i;

    switch (B_000C5C0C[1]) {
    case 0x7E:
        break;
    case 0:
        switch (B_000C5C0C[2]) {
        case 0x71:
            Sg2ModSetParam(B_000C5C08, 1, B_000C5C0C[3], 0);
            break;
        case 0x72:
            Sg2ModSetParam(B_000C5C08, 0x100, B_000C5C0C[3], B_000C5C0C[4]);
            break;
        case 0x73:
            Sg2ModSetParam(B_000C5C08, 4, B_000C5C0C[3], 0);
            break;
        case 0x74:
            Sg2ModSetParam(B_000C5C08, 8, B_000C5C0C[3], 0);
            break;
        case 0x76: {
            unsigned char *ev = B_000C5C0C;
            Sg2ModSetParam(B_000C5C08, 0x200,
                           ((ev[3] << 12) & 0xF000) | (ev[4] << 8 & 0xF00) | (ev[5] << 4 & 0xF0) | (ev[6] & 0xF), 0);
            break;
        }
        case 0x78:
            Sg2ModSetParam(B_000C5C08, 0x800, B_000C5C0C[3], 0);
            break;
        case 0x7C:
            all_soundoff(B_000C5C08);
            break;
        case 0x7D:
            all_keyoff(B_000C5C08);
            break;
        case 0x7E: {
            unsigned char *ev = B_000C5C0C;
            unsigned char type = ev[3];
            unsigned char th = ev[4];
            unsigned char tl = ev[5];
            unsigned char vh = ev[6];
            unsigned char vl = ev[7];
            unsigned char ch = ev[8];
            unsigned char note = ev[9];
            float t = 60.0 / Sg2CtrlGetTickMode();
            th <<= 4;
            vh <<= 4;
            th |= tl;
            vh |= vl;

            switch (type) {
            case 0:
                i = Sg2SlotFindVabChNote(buf, B_000C5C10[0], ch, note) - 1;
                for (; i >= 0; i--)
                    Sg2SlotSetTimePanParam(buf[i], (vh - Sg2SlotGetPan(buf[i])) * t / (th * 4), vh);
                break;
            case 1:
                i = Sg2SlotFindVabChNote(buf, B_000C5C10[0], ch, note) - 1;
                for (; i >= 0; i--)
                    Sg2SlotSetTimeVolParam(buf[i], (vh - Sg2SlotGetVol(buf[i])) * t / (th * 4), vh);
                break;
            case 2: {
                float p, d;
                i = Sg2SlotFindVabChNote(buf, B_000C5C10[0], ch, note) - 1;
                if (i >= 0) {
                    p = (signed char)vh;
                    p *= 1.19999993f;
                    d = p / (th * 4);
                    for (; i >= 0; i--)
                        Sg2SlotSetTimePitchParam(buf[i], d, p);
                }
                break;
            }
            }
            break;
        }
        case 0x7F: {
            unsigned char *ev = B_000C5C0C;
            unsigned char v;
            int a, b;
            int type = ev[3];
            v = ev[4];
            a = ev[5];
            b = ev[6];
            switch (type) {
            case 1:
                i = Sg2SlotFindSlotClassChNote(buf, B_000C5C10[1], a, b) - 1;
                for (; i >= 0; i--)
                    Sg2SlotSetLfoPitchDepth(buf[i], v);
                break;
            case 2:
                i = Sg2SlotFindSlotClassChNote(buf, B_000C5C10[1], a, b) - 1;
                for (; i >= 0; i--)
                    Sg2SlotSetLfoPitchSpeed(buf[i], v);
                break;
            }
            break;
        }
        }
        break;
    case 0x7F: {
        unsigned char *ev = B_000C5C0C;
        if (ev[2] == 0x7D && ev[3] == 4) {
            switch (ev[4]) {
            case 1:
                Sg2ModSetParam(B_000C5C08, 1, ev[6], 0);
                break;
            case 2:
                Sg2ModSetParam(B_000C5C08, 4, ev[6], 0);
                break;
            }
        }
        break;
    }
    }
}
#endif
