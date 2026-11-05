extern char D_0017A340[];

#ifdef NONMATCHING
void getStageChipIDReal(float *pos, int *x, int *z)
{
    *x = (int)((-pos[0] - *(float *)(D_0017A340 + 0x50)) / *(float *)(D_0017A340 + 0x40));
    *z = (int)((-pos[2] - *(float *)(D_0017A340 + 0x54)) / *(float *)(D_0017A340 + 0x44));
}
#endif
