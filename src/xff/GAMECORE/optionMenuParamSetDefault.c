typedef struct {
    char pad[0x314];
    int binding[10];
} OptionDefaults;
extern char gcGlobalVar[];
extern void _optionWorkSet(int, int);
extern int *_optionWorkPtr(int);
extern void setVibrationEnableWorkAdrs(int *);
extern void *getBrightness(void), *getScreenOffsetX(void), *getScreenOffsetY(void);
extern void *getFreeModeRevControlUD(void), *getFreeModeRevControlLR(void);
extern void *getFreeModeRevAngleVelRatio(void);
extern void *getSightOnRevCntrlUD(void), *getSightOnRevCntrlLR(void);
extern void setAspect(int);
void optionMenuParamSetDefault(void)
{
    OptionDefaults *defaults = (OptionDefaults *)gcGlobalVar;
    _optionWorkSet(0x11, 1);
    _optionWorkSet(3, 0);
    setVibrationEnableWorkAdrs(_optionWorkPtr(0x11));
    _optionWorkSet(1, *(int *)getBrightness());
    _optionWorkSet(4, *(int *)getScreenOffsetX());
    _optionWorkSet(5, *(int *)getScreenOffsetY());
    _optionWorkSet(2, 0);
    _optionWorkSet(6, 0);
    setAspect(-1);
    _optionWorkSet(0x12, *(int *)getFreeModeRevControlUD());
    _optionWorkSet(0x13, *(int *)getFreeModeRevControlLR());
    _optionWorkSet(0x14, *(int *)getFreeModeRevAngleVelRatio());
    _optionWorkSet(0x15, *(int *)getSightOnRevCntrlUD());
    _optionWorkSet(0x16, *(int *)getSightOnRevCntrlLR());
    _optionWorkSet(7, defaults->binding[6]);
    _optionWorkSet(8, defaults->binding[2]);
    _optionWorkSet(9, defaults->binding[4]);
    _optionWorkSet(10, defaults->binding[3]);
    _optionWorkSet(11, defaults->binding[5]);
    _optionWorkSet(12, defaults->binding[7]);
    _optionWorkSet(13, defaults->binding[8]);
    _optionWorkSet(14, defaults->binding[9]);
    _optionWorkSet(15, defaults->binding[0]);
    _optionWorkSet(16, defaults->binding[1]);
}
