extern float D_00136560;
extern float D_00136564;
extern float D_00136570;

float getZFogNear(void)
{
    return (D_00136570 - D_00136564) - D_00136560;
}
