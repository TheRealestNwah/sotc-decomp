extern void GetMotionMatrix(int, int, int, int, int, int);

void nico_IK_recomputeAll(int *p)
{
    GetMotionMatrix(p[2], p[3], p[4], p[1], p[45], p[46]);
}
