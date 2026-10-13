extern void nico_resetHorseRidingStatusForHorse(int);
extern void *GameObject_HORSE_B;
extern void *GameObject_HORSE_C;
extern void *GameObject_HORSE_D;
extern void *GameObject_HORSE_E;
extern void *GameObject_HORSE_F;
extern void *GameObject_HORSE_G;

void demo_end_resetHorseBridle(void)
{
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_B) + 8)));
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_C) + 8)));
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_D) + 8)));
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_E) + 8)));
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_F) + 8)));
    nico_resetHorseRidingStatusForHorse((*(int *)((char *)(GameObject_HORSE_G) + 8)));
}
