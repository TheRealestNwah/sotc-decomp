#ifdef NONMATCHING /* 98 diffs: case order and shared v[3] tail layout differ from the original switch */
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

int setVertexPos(float *v, unsigned char *s, int mode, float sx, float sy)
{
    int w;
    int h;
    float t;
    float lw;
    float rw;
    float th;
    float bh;

    switch (mode) {
    case 3:
        v[0] = *(float *)(s + 0x30);
        v[1] = *(float *)(s + 0x34) - sy * *(float *)(s + 0x44) * 0.5f;
        v[2] = *(float *)(s + 0x30) + sx * *(float *)(s + 0x40);
        t = sy * *(float *)(s + 0x44) * 0.5f;
        goto fin;
    case 4:
        v[0] = *(float *)(s + 0x30) - sx * *(float *)(s + 0x40) * 0.5f;
        v[1] = *(float *)(s + 0x34) - sy * *(float *)(s + 0x44) * 0.5f;
        v[2] = *(float *)(s + 0x30) + sx * *(float *)(s + 0x40) * 0.5f;
        t = sy * *(float *)(s + 0x44) * 0.5f;
        goto fin;
    case 5:
        v[0] = *(float *)(s + 0x30) - sx * *(float *)(s + 0x40);
        v[1] = *(float *)(s + 0x34) - sy * *(float *)(s + 0x44) * 0.5f;
        v[2] = *(float *)(s + 0x30);
        t = sy * *(float *)(s + 0x44) * 0.5f;
        goto fin;
    }
    goto skip;
fin:
    v[3] = *(float *)(s + 0x34) + t;
skip:
    w = getDrawScreenWidth() >> 1;
    h = getDrawScreenHeight() >> 1;
    lw = (float)-w;
    if (v[0] < lw && v[2] < lw) {
        return 1;
    }
    rw = (float)w;
    if (rw < v[0] && rw < v[2]) {
        return 1;
    }
    th = (float)-h;
    if (v[1] < th && v[3] < th) {
        return 1;
    }
    bh = (float)h;
    if (bh < v[1] && bh < v[3]) {
        return 1;
    }
    return 0;
}
#endif
