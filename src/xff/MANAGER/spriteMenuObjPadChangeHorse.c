extern void mcGetCompleteTimeAttack(int *, int *);
typedef struct { int pad[2]; int trigger; } PadManagerData;
extern PadManagerData padManagerData;
extern signed char *D_00136E78;

static inline int padBit(int key)
{
    return 1 << key;
}

int spriteMenuObjPadChangeHorse(void)
{
    int normal, hard;
    mcGetCompleteTimeAttack(&normal, &hard);
    if (hard != 0 && normal != 0 && (padManagerData.pad[0] & padBit(D_00136E78[11])))
        return 1;
    if ((hard != 0 || normal != 0) && (padManagerData.pad[0] & padBit(D_00136E78[12])))
        return 2;
    return 0;
}
