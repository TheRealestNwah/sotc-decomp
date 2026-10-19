extern int GetMotionFrame(float *, float *, int, float, float);
void GetAnimationClassCurrentInfo(void *object, int resource, float rate, float delta)
{
    char *state = object;
    *(int *)(state + 0x20) = GetMotionFrame((float *)(state + 8), (float *)(state + 0x18), resource,
        rate * *(float *)(state + 0x1C) * *(float *)(state + 0x28), delta);
}
