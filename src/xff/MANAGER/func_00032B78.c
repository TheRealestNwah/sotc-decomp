typedef union {
    unsigned int w;
    unsigned short h;
    float f;
} PackedWord;

typedef struct {
    float base0, scale0;
    float base1, scale1;
    float base2, scale2;
    void *data;
} PackedTrack;

static void func_00032B78(float *out, int type, PackedTrack *t, int frame)
{
    PackedWord *w;

    out[3] = 1.0f;
    switch (type) {
    case 3:
        w = (PackedWord *)((unsigned short *)t->data + frame);
        out[0] = (int)(w->h >> 11) * t->scale0 * (1.0f / 31.0f) + t->base0;
        out[1] = (int)((w->h >> 5) & 0x3F) * t->scale1 * (1.0f / 31.0f) + t->base1;
        out[2] = (int)(w->h & 0x1F) * t->scale2 * (1.0f / 31.0f) + t->base2;
        break;
    case 2:
        w = (PackedWord *)t->data + frame;
        out[0] = (int)(w->w >> 21) * t->scale0 * (1.0f / 2047.0f) + t->base0;
        out[1] = (int)((w->w >> 10) & 0x7FF) * t->scale1 * (1.0f / 2047.0f) + t->base1;
        out[2] = (int)(w->w & 0x3FF) * t->scale2 * (1.0f / 1023.0f) + t->base2;
        break;
    case 0:
        out[0] = t->base0;
        out[1] = t->scale0;
        out[2] = t->base1;
        break;
    default:
        out[0] = ((float *)t)[frame * 3 + 0];
        out[1] = ((float *)t)[frame * 3 + 1];
        out[2] = ((float *)t)[frame * 3 + 2];
        break;
    }
}
