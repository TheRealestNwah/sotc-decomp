extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void nico_resetHorseRidingStatusForHorse(int);

void demo_brige_resetHorseBridle(void)
{
    nico_resetHorseRidingStatusForHorse((int)SCRGetFirstObj(gcGlobalVar + 0x2B4));
}
