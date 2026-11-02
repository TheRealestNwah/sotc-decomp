extern float iosGetRandom(void);
extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

void AI_GetRandomCylinderOfs(float *out, float minR, float maxR, float minH, float maxH)
{
    float a;
    float r;
    float h;
    short ang;

    a = iosGetRandom() * 2.0f * 3.14159265f;
    r = minR + (maxR - minR) * iosGetRandom();
    ang = a * 32768.0f / 3.14159265f;
    out[0] = iosGetTableSin(ang) * r;
    out[1] = 0.0f;
    out[2] = iosGetTableCos(ang) * r;
    out[3] = 0.0f;
    h = minH + (maxH - minH) * iosGetRandom();
    out[1] = iosGetRandom() - 0.5f < 0.0f ? -h : h;
}
