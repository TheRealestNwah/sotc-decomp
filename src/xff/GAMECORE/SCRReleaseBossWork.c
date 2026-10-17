extern void bosslifebar_sethp(float);
extern void effect_blood_free(void *);
extern void end_weakpoint_effect(void);
extern void isysRequestDeleteObj(void *);
extern void BossSprStatusEnd(void);
void SCRReleaseBossWork(char *work)
{
    int i;
    int j;
    bosslifebar_sethp(0.0f);
    if (*(void **)(work + 0x50) != 0) {
        effect_blood_free(*(void **)(work + 0x50));
        *(void **)(work + 0x50) = 0;
    }
    end_weakpoint_effect();
    for (i = 0; i < *(int *)(work + 8); ++i) {
        void *object = (void *)((int *)*(int *)(work + 0x5C))[i];
        if (object != 0)
            isysRequestDeleteObj(object);
    }
    for (j = 0; j < *(int *)(work + 8); ++j)
        ((int *)*(int *)(work + 0x5C))[j] = 0;
    BossSprStatusEnd();
}
