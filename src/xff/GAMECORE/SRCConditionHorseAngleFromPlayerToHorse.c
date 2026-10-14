#ifdef NONMATCHING
extern void *GetSCRCharaAIWorkPtr(void *);

int SRCConditionHorseAngleFromPlayerToHorse(void *actor, float fparg0, float fparg1) {
    float temp_f1;
    int var_v0;
    int var_v1;

    temp_f1 = (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x4234));
    var_v0 = 0;
    var_v1 = 0;
    if (temp_f1 != -1.0f) {
        var_v0 = 0;
        if ((fparg0 * 0.0174532925f) <= temp_f1) {
            if (temp_f1 <= (fparg1 * 0.0174532925f)) {
                var_v1 = 1;
            }
            var_v0 = var_v1;
        }
    }
    return var_v0;
}

#else
extern int SRCConditionHorseAngleFromPlayerToHorse(void *, float, float);
#endif
