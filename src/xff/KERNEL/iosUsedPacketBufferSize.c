typedef struct { int start[2]; int c, d; int ptr; int e; int cur; } DlState;
extern DlState B_00065018;
extern int D_00040AFC;

float iosUsedPacketBufferSize(void)
{
    return (float)(unsigned int)(B_00065018.ptr - B_00065018.start[B_00065018.cur]) / (float)(D_00040AFC * 16);
}
