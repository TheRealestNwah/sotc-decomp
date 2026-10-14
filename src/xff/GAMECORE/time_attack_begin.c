extern int ScrIntrDef_TIMEATTACK_MENU_START;
extern int scriptIntrSignal();

int time_attack_begin(void)
{
    return scriptIntrSignal(ScrIntrDef_TIMEATTACK_MENU_START);
}
