extern char gcGlobalVar[];
extern int SCRGetFirstObj();
extern int nico_ResetPlayerHorseRidingControl();

int demo_brige_resetHorseParent(void)
{
    return nico_ResetPlayerHorseRidingControl(SCRGetFirstObj((int)(gcGlobalVar + 0x2B4)));
}
