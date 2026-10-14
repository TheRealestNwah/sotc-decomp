extern float GetWaterSurfacePositionYExtend(int, int, int, int, float, float, float);

float GetWaterSurfacePositionY(int a, int b, int c, float x, float y)
{
    return GetWaterSurfacePositionYExtend(a, b, c, 0, x, y, 0.0f);
}
