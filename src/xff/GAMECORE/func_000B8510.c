typedef struct {
    char pad0[0x150];
    int cmd;
    char pad154[8];
    int next;
    int state;
    char pad164[4];
    int changed;
    char pad16C[0x198];
    int impact;
} SmallWork;

extern int isysGetThisSubThread(void);
extern int AI_CheckDamage_Bow(int, int);
extern int AI_CheckDamage_SoundBow(int, int);
extern int AI_CheckDamage_Impact(int, int);

static void func_000B8510(SmallWork *w)
{
    int th = isysGetThisSubThread();

    w->changed = 0;
    switch (w->state) {
    case 3:
        if (w->cmd == 0x21) { w->next = 3; w->changed = 1; }
        break;
    case 4:
        if (w->cmd == 0x22) { w->next = 4; w->changed = 1; }
        break;
    case 1:
        if (w->cmd == 0x22) { w->next = 1; w->changed = 1; }
        break;
    case 2:
        if (w->cmd == 0x23) { w->next = 2; w->changed = 1; }
        break;
    case 6:
        if (w->cmd == 0x23) { w->next = 6; w->changed = 1; }
        break;
    case 7:
        if (w->cmd == 0x22) { w->next = 7; w->changed = 1; }
        break;
    case 8:
        if (w->cmd == 0x23) { w->next = 8; w->changed = 1; }
        break;
    case 9:
        if (w->cmd == 0x23) { w->next = 9; w->changed = 1; }
        break;
    case 10:
        if (w->cmd == 0x23) { w->next = 10; w->changed = 1; }
        break;
    case 12:
        if (w->cmd == 0x22) { w->next = 12; w->changed = 1; }
        break;
    case 11:
        if (w->cmd == 0x23) { w->next = 11; w->changed = 1; }
        break;
    case 13:
        if (w->cmd == 0x23) { w->next = 13; w->changed = 1; }
        break;
    }
    if (w->cmd == 0x25 || AI_CheckDamage_Bow(0, th) || AI_CheckDamage_SoundBow(0, th)
        || (w->impact != 0 && AI_CheckDamage_Impact(0, th))) {
        if (w->state == 0xF) {
            w->next = 0xF;
            w->changed = 1;
        } else {
            w->next = 0xE;
            w->changed = 1;
        }
    }
}
