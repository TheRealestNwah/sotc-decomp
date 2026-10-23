typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char pad[5];
} CdState;
extern CdState B_00046540;
extern CdState B_00046548;
extern CdState *B_00046550;

void iosCdSetMode(int mode)
{
    CdState **target = &B_00046550;
    CdState *state;
    if (mode == 1)
        state = &B_00046540;
    else
        state = &B_00046548;
    *target = state;
}
