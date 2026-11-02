extern unsigned int D_00130380;
extern int D_00130388;
extern float D_0013038C;
extern float B_00147300[2];

void setBossDeathEffect(unsigned int x, unsigned int y, float time)
{
    D_00130380 |= 1;
    D_00130388 = 0;
    D_0013038C = time;
    B_00147300[0] = x * (1.0f / 4096.0f);
    B_00147300[1] = y * (1.0f / 4096.0f);
}
