extern int isysGetThisSubThread(void);
extern int AI_CheckDamage_Bow(int, int);
extern int AI_CheckDamage_Sword(int, int);
extern int AI_CheckDamage_SoundBow(int, int);
extern int AI_CheckDamage_Impact(int, int);

static void func_0009C4D8(char *s)
{
    int th = isysGetThisSubThread();
    int st;
    int m;

    *(int *)(s + 0x1B0) = 0;
    st = *(int *)(s + 0x1A0);
    switch (st) {
    case 0:
        if (*(int *)(s + 0x190) == 0xC) {
            *(int *)(s + 0x1B0) = 1;
            *(int *)(s + 0x19C) = 0;
        }
        break;
    case 1:
        if (*(int *)(s + 0x190) == 0xD) {
            *(int *)(s + 0x19C) = 1;
            *(int *)(s + 0x1B0) = 1;
        }
        break;
    case 2:
        if (*(int *)(s + 0x190) == 0xD) {
            *(int *)(s + 0x19C) = st;
            *(int *)(s + 0x1B0) = 1;
        }
        break;
    case 3:
        if (*(int *)(s + 0x190) == 0xD) {
            *(int *)(s + 0x19C) = st;
            *(int *)(s + 0x1B0) = 1;
        }
        break;
    }
    m = *(int *)(s + 0x1A4);
    if (m == 4 || m == 6) {
        *(int *)(s + 0x19C) = m;
        *(int *)(s + 0x1B0) = 1;
    }
    if (*(int *)(s + 0x19C) < 5) {
        if (AI_CheckDamage_Bow(0, th) || AI_CheckDamage_Sword(0, th) || AI_CheckDamage_SoundBow(0, th)
            || (*(int *)(s + 0x274) != 0 && AI_CheckDamage_Impact(0, th))) {
            *(int *)(s + 0x19C) = 5;
            *(int *)(s + 0x1B0) = 1;
        }
    }
}
