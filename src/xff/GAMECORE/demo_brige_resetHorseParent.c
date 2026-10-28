extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void nico_ResetPlayerHorseRidingControl(void *);

void demo_brige_resetHorseParent(void)
{
    nico_ResetPlayerHorseRidingControl(SCRGetFirstObj(gcGlobalVar + 0x2B4));
}
