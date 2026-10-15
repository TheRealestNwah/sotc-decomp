typedef struct { int start; float ofs; } VTime;
extern volatile int D_00040D64;

void addVIntrTime(VTime *t, float dt)
{
    float f = D_00040D64 - t->start;
    int n = f * 0.01668335f;
    float sec = (float)n + (f - (float)n * 59.94f) * 0.01668335f;
    t->ofs = dt - sec;
}
