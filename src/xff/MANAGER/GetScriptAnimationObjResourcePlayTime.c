typedef struct { int f0; unsigned int w; } MotionRes;

float GetScriptAnimationObjResourcePlayTime(unsigned char *obj)
{
    unsigned char *o;
    MotionRes *res;
    float scale;
    unsigned int rate;

    o = obj[8] == 0xD ? obj + 0x20 : 0;
    res = *(MotionRes **)(o + 0x334);
    scale = 1.0f;
    rate = res->w;
    rate >>= 20;
    if (rate != 0) {
        scale = (float)rate * 0.000244140625f;
    }
    return (float)(*(short *)((char *)res + 4) - 1) * 0.033333331346511841f / scale;
}
