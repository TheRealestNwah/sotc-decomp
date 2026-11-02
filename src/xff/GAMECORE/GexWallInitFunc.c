extern float iosGetTableSin(short);
extern float iosGetTableCos(short);
extern void GetInitWallFunc(void *, void *, void *, void *, void *, float *);

void GexWallInitFunc(void *a, void *b, void *c, void *d, void *e)
{
    float v[4];

    v[0] = iosGetTableSin(*(short *)((char *)d + 0x1C) * 0.0174532925f * 32768.0f / 3.14159265f);
    v[1] = 0.0f;
    v[2] = iosGetTableCos(*(short *)((char *)d + 0x1C) * 0.0174532925f * 32768.0f / 3.14159265f);
    v[3] = 0.0f;
    GetInitWallFunc(a, b, c, d, e, v);
}
