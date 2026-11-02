typedef struct { int f0; unsigned int w; } MotionRes;
extern int GetMotionFrameDirectResource(float *, float *, MotionRes *, float);
void GetAnimationClassCurrentInfoDirectResource(void *object, MotionRes *res, float rate)
{
    char *state = object;
    float scale;
    unsigned int frames;
    float *end;

    scale = 1.0f;
    frames = res->w;
    frames >>= 20;
    end = (float *)(state + 0x18);
    if (frames != 0) {
        scale = (float)frames * 0.000244140625f;
    }
    *(int *)(state + 0x20) =
        GetMotionFrameDirectResource((float *)(state + 8), end, res, rate * *(float *)(state + 0x1C) * scale);
}
