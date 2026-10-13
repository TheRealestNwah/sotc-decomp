extern int GetMotionFrame(int, int, int, float);

void GetAnimationClassCurrentInfo(void *arg0, int arg1, float fparg0)
{
    (*(int *)((char *)(arg0) + 0x20)) = GetMotionFrame(arg0 + 8, arg0 + 0x18, arg1, fparg0 * (*(float *)((char *)(arg0) + 0x1C)) * (*(float *)((char *)(arg0) + 0x28)));
}
