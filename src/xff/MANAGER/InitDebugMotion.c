extern void *iosgluCreateObject(void *);
extern void iosgluAddCylinderObject(void *, float, float, int, int, float);
extern void iosgluAddLineCylinderObject(void *, float, float, int, int, float);
extern void *B_00148A10[];

void InitDebugMotion(void *partition)
{
    B_00148A10[0] = iosgluCreateObject(partition);
    iosgluAddCylinderObject(B_00148A10[0], 0.01f, 0.01f, 3, 1, 1.0f);
    B_00148A10[1] = iosgluCreateObject(partition);
    iosgluAddCylinderObject(B_00148A10[1], 0.01f, 0.01f, 4, 1, 1.0f);
    B_00148A10[2] = iosgluCreateObject(partition);
    iosgluAddLineCylinderObject(B_00148A10[2], 0.01f, 0.01f, 4, 1, 1.0f);
}
