extern int ClipCollisionDB(void *, float *, float *, void *);

int ClipCollisionDBDoubleSide(void *out, float *a, float *b, void *geometry)
{
    int result = 0;
    if (ClipCollisionDB(out, a, b, geometry) != 0 ||
        ClipCollisionDB(out, b, a, geometry) != 0)
        result = 1;
    return result;
}
