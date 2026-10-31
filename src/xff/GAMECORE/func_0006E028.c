extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern void *GetCollisionDBPlane(void *);
extern float GetPlaneSlopeDegree(void *);

static int func_0006E028(void *col)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(col) & 0x7C000000;

    if (70.0f < __builtin_fabsf(GetPlaneSlopeDegree(GetCollisionDBPlane(col))))
        return 0;
    return attr == 0x34000000;
}
