extern int texGetCSM1Idx(int);

#define C(i) ((unsigned char *)(clut + texGetCSM1Idx(i) * 4))

int SpriteSetStatusClut(char *clut, float *st, int cnt)
{
    float cur;
    float tgt;
    unsigned char n;
    int a;
    int b;
    int i;
    int ret;

    n = C(0xFF)[3];
    ret = cnt + 1;
    cur = st[2];
    tgt = st[0];
    if (tgt < cur) {
        cur -= 0.01f;
        st[2] = cur;
        if (cur <= tgt) {
            st[2] = tgt;
            ret = 0;
            cur = tgt;
        }
    }
    if (cur < tgt) {
        cur += 0.01f;
        st[2] = cur;
        if (tgt <= cur) {
            st[2] = tgt;
            ret = 0;
            cur = tgt;
        }
    }
    a = cur * n + 1.5f;
    b = tgt * n + 1.5f;
    for (i = a; i <= n; i++) {
        C(i)[0] = C(0xFE)[0];
        C(i)[1] = C(0xFE)[1];
        C(i)[2] = C(0xFE)[2];
        C(i)[3] = C(0xFE)[3];
    }
    for (i = b; i < a; i++) {
        C(i)[0] = (C(0xFC)[0] + (C(0xFD)[0] - C(0xFC)[0]) * i / n) >> 1;
        C(i)[1] = (C(0xFC)[1] + (C(0xFD)[1] - C(0xFC)[1]) * i / n) >> 1;
        C(i)[2] = (C(0xFC)[2] + (C(0xFD)[2] - C(0xFC)[2]) * i / n) >> 1;
        C(i)[3] = C(0xFC)[3] + (C(0xFD)[3] - C(0xFC)[3]) * i / n;
    }
    for (i = 1; i < b; i++) {
        C(i)[0] = C(0xFC)[0] + (C(0xFD)[0] - C(0xFC)[0]) * i / n;
        C(i)[1] = C(0xFC)[1] + (C(0xFD)[1] - C(0xFC)[1]) * i / n;
        C(i)[2] = C(0xFC)[2] + (C(0xFD)[2] - C(0xFC)[2]) * i / n;
        C(i)[3] = C(0xFC)[3] + (C(0xFD)[3] - C(0xFC)[3]) * i / n;
    }
    return ret;
}
