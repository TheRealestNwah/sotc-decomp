extern int D_00040624;
extern float D_00040628[];

float iosGetCpuRapCountPar1Int(void)
{
    return (float)*(volatile unsigned int *)0x10000800 * 60.0f / D_00040628[D_00040624];
}
