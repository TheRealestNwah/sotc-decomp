extern int GetMotionResourceOriginalFrames(void *);
int GetMotionResourceFrames(void *resource)
{
    return GetMotionResourceOriginalFrames(resource) - 1;
}