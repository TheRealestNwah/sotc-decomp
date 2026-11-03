typedef struct {
    float base[2];
    float y[2];
    float z[2];
    short *data;
} PosQuant;

void getPosPQSAnimIntFrame(float *out, unsigned char *b, int frame)
{
    float *d = *(float **)(b + 4);
    int type = b[2];

    if (d != 0) {
        out[3] = 1.0f;
        switch (type) {
        default: {
            float *p = d + frame * 3;

            out[0] = p[0];
            out[1] = p[1];
            out[2] = p[2];
            break;
        }
        case 2: {
            PosQuant *q = (PosQuant *)d;
            short *s = q->data + frame * 3;

            out[0] = s[0] * q->base[1] * (1.0f / 32767.0f) + q->base[0];
            out[1] = s[1] * q->y[1] * (1.0f / 32767.0f) + q->y[0];
            out[2] = s[2] * q->z[1] * (1.0f / 32767.0f) + q->z[0];
            break;
        }
        case 0:
            out[0] = d[0];
            out[1] = d[1];
            out[2] = d[2];
            break;
        }
    }
}
