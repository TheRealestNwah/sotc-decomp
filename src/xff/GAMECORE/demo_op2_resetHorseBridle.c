extern int gStatGetHorseDemoISYSObj();
extern void nico_resetHorseRidingStatusForHorse(int);

void demo_op2_resetHorseBridle(void)
{
    int o = gStatGetHorseDemoISYSObj();

    if (o != 0) {
        nico_resetHorseRidingStatusForHorse(o);
    }
}
