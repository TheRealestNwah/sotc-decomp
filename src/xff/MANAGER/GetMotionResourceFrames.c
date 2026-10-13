extern int GetMotionResourceOriginalFrames();

int GetMotionResourceFrames(void)
{
    return GetMotionResourceOriginalFrames() - 1;
}
