extern char *ForceAcceptMotion(char *, char *, float);
extern void InitAnimationClass(void *, char *);
extern void ResetCharacterClassAnimeFrameTableInfo(char *);

void ResetCharacterClassMotionShiftInfo(char *character, char *motion, float frame)
{
    ForceAcceptMotion(character, motion, frame);
    InitAnimationClass(character + 0x1C0, motion);
    ResetCharacterClassAnimeFrameTableInfo(character);
}
