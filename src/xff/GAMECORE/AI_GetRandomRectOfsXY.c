extern float iosGetRandom(void);

void AI_GetRandomRectOfsXY(float *out, float minX, float maxX, float minY, float maxY)
{
    float sx, sy, t, t2, n, r;

    out[0] = (iosGetRandom() * 2.0f - 1.0f) * maxX;
    out[1] = (iosGetRandom() * 2.0f - 1.0f) * maxY;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (out[0] < minX && out[1] < minY) {
        sx = (maxX - minX) / minX;
        sy = (maxY - minY) / minY;
        t = out[0] * sx;
        if (out[0] < out[2]) {
            n = -minX;
            r = n + t;
        } else {
            r = minX + t;
        }
        out[0] = r;

        t2 = out[1] * sy;
        if (out[1] < 0.0f) {
            n = -minY;
            out[1] = n + t2;
        } else {
            out[1] = minY + t2;
        }
    }
}
