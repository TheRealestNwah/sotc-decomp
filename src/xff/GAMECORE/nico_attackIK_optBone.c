extern char B_001A5B30[];
extern void GetMotionNodeQuaternionPos(void *, void *, int, int, int);
void nico_attackIK_optBone(int *p)
{
    int buf[4] __attribute__((aligned(16)));
    GetMotionNodeQuaternionPos(B_001A5B30, buf, p[0], p[5], 0);
}
