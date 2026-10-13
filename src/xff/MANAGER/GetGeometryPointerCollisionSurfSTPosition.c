extern int CheckLegalCollisionGP(void *);

int GetGeometryPointerCollisionSurfSTPosition(float *arg0, float *arg1, void *arg2)
{
    if (CheckLegalCollisionGP(arg2) != 0) {
        *arg0 = (*(float *)((char *)(arg2) + 8));
        *arg1 = (*(float *)((char *)(arg2) + 0xC));
        return 0;
    }
    return -1;
}
