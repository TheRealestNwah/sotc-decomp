extern void GetMotionRootIntFrame(void *, void *, int);
extern void GetMotionRootFloatFrame(void *, void *, float);
extern int GetMotionResourceFrames(void *);
void GetCharacterClassCurrentAnimationPositionInfo(void *out, unsigned char *cls, int mode)
{
    unsigned char *anim = cls + 0x1C0;
    unsigned char *motion = *(unsigned char **)anim + 0x50;
    switch (mode) {
    case 0:
        GetMotionRootIntFrame(out, motion, 0);
        break;
    case 1:
        GetMotionRootFloatFrame(out, motion, *(float *)(anim + 8));
        break;
    case 2:
        GetMotionRootIntFrame(out, motion, GetMotionResourceFrames(motion));
        break;
    }
}