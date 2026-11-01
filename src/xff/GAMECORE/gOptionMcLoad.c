typedef struct { char b[0x88]; } OptionData;

extern OptionData B_00183E68;
extern int mcRead(int, void *, int);
extern void optionMenuParamSetLoadData(void);

int gOptionMcLoad(int port)
{
    OptionData save = B_00183E68;
    int r = mcRead(port, &B_00183E68, 0x88);
    if (r == 0) {
        optionMenuParamSetLoadData();
    } else {
        B_00183E68 = save;
    }
    return r;
}
