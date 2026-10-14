extern float D_0017A304;

void addPlayerO2(float add)
{
    float v = D_0017A304 + add;
    float r;
    if (100.0f < v)
        r = 100.0f;
    else if (v < 0.0f)
        r = 0.0f;
    else
        r = v;
    D_0017A304 = r;
}
