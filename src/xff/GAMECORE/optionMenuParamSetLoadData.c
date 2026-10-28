typedef struct {
    char pad[0x314];
    int binding[10];
} OptionBindings;
extern OptionBindings gcGlobalVar;
extern int _optionWorkChk(int);
extern void *getBrightness(void), *getScreenOffsetX(void), *getScreenOffsetY(void);
extern void *getFreeModeRevControlUD(void), *getFreeModeRevControlLR(void);
extern void *getFreeModeRevAngleVelRatio(void);
extern void *getSightOnRevCntrlUD(void), *getSightOnRevCntrlLR(void);
extern void setAspect(int);
extern int setSoundMode(int);
extern void setZoomKey(int), setInterestKey(int), setBossInterestKey(int);
void optionMenuParamSetLoadData(void)
{
    int *setting;
    setting = getBrightness();
    *setting = _optionWorkChk(1);
    setting = getScreenOffsetX();
    *setting = _optionWorkChk(4);
    setting = getScreenOffsetY();
    *setting = _optionWorkChk(5);
    setAspect(-1);
    setSoundMode(_optionWorkChk(3));
    setting = getFreeModeRevControlUD();
    *setting = _optionWorkChk(0x12);
    setting = getFreeModeRevControlLR();
    *setting = _optionWorkChk(0x13);
    setting = getFreeModeRevAngleVelRatio();
    *setting = _optionWorkChk(0x14);
    setting = getSightOnRevCntrlUD();
    *setting = _optionWorkChk(0x15);
    setting = getSightOnRevCntrlLR();
    *setting = _optionWorkChk(0x16);
    gcGlobalVar.binding[6] = _optionWorkChk(7);
    gcGlobalVar.binding[2] = _optionWorkChk(8);
    gcGlobalVar.binding[4] = _optionWorkChk(9);
    gcGlobalVar.binding[3] = _optionWorkChk(10);
    gcGlobalVar.binding[5] = _optionWorkChk(11);
    gcGlobalVar.binding[7] = _optionWorkChk(12);
    gcGlobalVar.binding[8] = _optionWorkChk(13);
    gcGlobalVar.binding[9] = _optionWorkChk(14);
    gcGlobalVar.binding[0] = _optionWorkChk(15);
    gcGlobalVar.binding[1] = _optionWorkChk(16);
    setZoomKey(_optionWorkChk(13));
    setInterestKey(_optionWorkChk(14));
    setBossInterestKey(_optionWorkChk(12));
}
