typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;

void ResetCharacterClassMotionInterpRootOfs(char *c)
{
    char *motion = *(char **)(c + 0x358);

    *(s128 *)(c + 0x6D0) = ZeroPoint;
    if (motion) {
        *(float *)(c + 0x6D4) = *(float *)(motion + 0x14);
    }
}
