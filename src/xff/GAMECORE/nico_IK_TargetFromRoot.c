extern int GetMotionMatrixOfTargetFromRoot();

int nico_IK_TargetFromRoot(int *p)
{
    return GetMotionMatrixOfTargetFromRoot(p[2], p[3], p[4], p[1], p[0x2D], p[0x2E], p[5]);
}
