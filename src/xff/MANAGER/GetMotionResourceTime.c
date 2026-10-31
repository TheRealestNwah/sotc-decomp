typedef struct { int f0; unsigned int w; } MotionRes;
float GetMotionResourceTime(MotionRes *res, float fps)
{
    float scale;
    unsigned int rate;

    scale = 1.0f;
    rate = res->w;
    rate >>= 20;
    if (rate != 0) {
        scale = (float)rate * 0.000244140625f;
    }
    return (float)(*(short *)((char *)res + 4) - 1) * (1.0f / fps) / scale;
}
