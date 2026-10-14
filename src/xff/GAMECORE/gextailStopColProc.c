extern int SetCharacterObjCollisionProcFlag();

int gextailStopColProc(int a, int b, int c, int d)
{
    return SetCharacterObjCollisionProcFlag(a, 0, c, d);
}
