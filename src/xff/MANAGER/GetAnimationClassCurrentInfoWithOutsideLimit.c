extern int GetMotionFrameWithOutsideLimit(float *, float *, int, float, float);
void GetAnimationClassCurrentInfoWithOutsideLimit(void *object, int limit, float rate, float delta)
{
    char *state = object;
    *(int *)(state + 0x20) = GetMotionFrameWithOutsideLimit((float *)(state + 8),
        (float *)(state + 0x18), limit, rate * *(float *)(state + 0x1C), delta);
}
