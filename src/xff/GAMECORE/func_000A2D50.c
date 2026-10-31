typedef struct {
    char pad0[0x260];
    int event;
    char pad264[0x26C - 0x264];
    int mode;
    char pad270[0x278 - 0x270];
    int state;
    int sub;
    int changed;
    char pad284[0x7BC - 0x284];
    int damaged;
    char pad7C0[0x7C4 - 0x7C0];
    int impact;
} Kite;

extern void *isysGetThisSubThread(void);
extern int AI_CheckDamage_Bow(int, void *);
extern int AI_CheckDamage_Sword(int, void *);
extern int AI_CheckDamage_SoundBow(int, void *);
extern int AI_CheckDamage_Impact(int, void *);

static inline void setMode(Kite *k, int mode)
{
    k->mode = mode;
    k->changed = 1;
}

static void func_000A2D50(Kite *k)
{
    void *th = isysGetThisSubThread();

    k->changed = 0;
    switch (k->state) {
    case 2:
        if (k->event == 0x1D)
            setMode(k, 2);
        break;
    case 4:
        if (k->event == 0x1E)
            setMode(k, 4);
        break;
    case 6:
        if (k->event == 0x1F)
            setMode(k, 6);
        break;
    case 5:
        if (k->event == 0x1F)
            setMode(k, 5);
        break;
    case 20:
        if (k->event == 0x1E)
            setMode(k, 20);
        break;
    }
    switch (k->sub) {
    case 0:
        setMode(k, 0);
        break;
    case 7:
        setMode(k, 7);
        break;
    case 9:
        setMode(k, 9);
        break;
    case 13:
        setMode(k, 13);
        break;
    case 14:
        setMode(k, 14);
        break;
    case 15:
        setMode(k, 15);
        break;
    case 16:
        setMode(k, 16);
        break;
    case 19:
        setMode(k, 19);
        break;
    }
    if (k->mode < 18 && k->event == 0x21) {
        setMode(k, 18);
        k->damaged = 0;
    }
    if (k->mode < 18) {
        if (AI_CheckDamage_Bow(0, th) || AI_CheckDamage_Sword(0, th) || AI_CheckDamage_SoundBow(0, th)
            || (k->impact && AI_CheckDamage_Impact(0, th)))
            k->damaged = 1;
    }
}
