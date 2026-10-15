extern void func_000ADFC8(void *, float *);

void GetCollisionDBRegion(void *db, float *out, float base)
{
    float t[4];
    func_000ADFC8(db, t);
    *out = base + t[0];
}
