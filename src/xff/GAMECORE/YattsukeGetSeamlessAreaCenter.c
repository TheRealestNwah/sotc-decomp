void YattsukeGetSeamlessAreaCenter(float *center, int area)
{
    int x = (area % 10) * 600 - 2700;

    center[0] = -x;
    center[1] = 0.0f;
    center[2] = (area / 10) * 600 - 2700;
    center[3] = 1.0f;
}
