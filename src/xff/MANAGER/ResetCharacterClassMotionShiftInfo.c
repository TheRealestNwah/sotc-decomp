extern void ForceAcceptMotion();
extern void InitAnimationClass(int, int);
extern void ResetCharacterClassAnimeFrameTableInfo(int);

void ResetCharacterClassMotionShiftInfo(int arg0, int arg1)
{
    ForceAcceptMotion();
    InitAnimationClass(arg0 + 0x1C0, arg1);
    ResetCharacterClassAnimeFrameTableInfo(arg0);
}
