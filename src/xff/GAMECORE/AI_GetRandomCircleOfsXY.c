extern float iosGetRandom(void);
extern float iosGetTableCos(short);
extern float iosGetTableSin(short);

void AI_GetRandomCircleOfsXY(float *out, float min, float max)
{
    float a = iosGetRandom() * 2.0f * 3.1415926f;
    float r = min + (max - min) * iosGetRandom();
    short ang = (int)(a * 32768.0f / 3.1415926f);

    out[0] = iosGetTableCos(ang) * r;
    out[1] = -iosGetTableSin(ang) * r;
    out[2] = 0.0f;
    out[3] = 0.0f;
}
