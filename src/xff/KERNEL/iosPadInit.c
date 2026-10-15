extern char iosDefaultPadData[];
extern int ShockVoiceSetCommon;
extern void Init_Shock(void);
extern void Shock_SetShockVoiceSet(int, int);
extern void Init_Controler(void *);
extern void Init_Player(void *);

void iosPadInit(void)
{
    Init_Shock();
    Shock_SetShockVoiceSet(0, ShockVoiceSetCommon);
    Init_Controler(iosDefaultPadData + 0x6C);
    Init_Controler(iosDefaultPadData + 0xE4);
    Init_Player(iosDefaultPadData + 0x58);
    Init_Player(iosDefaultPadData + 0xD0);
}
