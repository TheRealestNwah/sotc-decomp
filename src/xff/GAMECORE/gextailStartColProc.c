extern int SetCharacterObjCollisionProcFlag();

int gextailStartColProc(int a, int b, int c, int d)
{
    return SetCharacterObjCollisionProcFlag(a, 1, c, d);
}
