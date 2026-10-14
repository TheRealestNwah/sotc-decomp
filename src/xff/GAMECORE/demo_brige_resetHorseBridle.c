extern char gcGlobalVar[];
extern int SCRGetFirstObj();
extern int nico_resetHorseRidingStatusForHorse();

int demo_brige_resetHorseBridle(void)
{
    return nico_resetHorseRidingStatusForHorse(SCRGetFirstObj((int)(gcGlobalVar + 0x2B4)));
}
