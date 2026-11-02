extern char *GetSpriteClass(void *);
extern char gcGlobalVar[];

void spritedisplay(void *spr, int on)
{
    char *c = GetSpriteClass(spr);
    float now = *(float *)(gcGlobalVar + 0x168);
    float t = *(float *)(c + 0x34);
    float v = *(float *)(c + 0x30);

    if (t != 0.0f) {
        float d = now - t;

        if (on) {
            v = v + d / *(float *)(c + 0x3C);
            v = v < 1.0f ? v : 1.0f;
        } else {
            v = v - d / (*(float *)(c + 0x44) - *(float *)(c + 0x40));
            v = 0.0f < v ? v : 0.0f;
        }
    }
    if ((0.0f < v && v < 1.0f) || (v == 0.0f && on) || (v == 1.0f && !on))
        *(float *)(c + 0x34) = now;
    else
        *(float *)(c + 0x34) = 0.0f;
    *(float *)(c + 0x30) = v;
    if (v != 0.0f)
        (*(void (**)(void *))(c + 0x54))(spr);
}
