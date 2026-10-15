typedef struct { int start; float ofs; } VTime;
extern volatile int D_00040D64;

float getVIntrDiffTime(VTime *t)
{
    float f = D_00040D64 - t->start;
    int n = f * 0.01668335f;
    return (float)n + (f - (float)n * 59.94f) * 0.01668335f + t->ofs;
}
