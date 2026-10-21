typedef struct { int start; float ofs; } VTime;
extern volatile int D_00040D64;

void setVIntrBaseTime(VTime *time)
{
    time->start = D_00040D64;
    time->ofs = 0.0f;
}
