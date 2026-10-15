typedef struct { char a, b, c; } Bool3;
extern void func_00033B88(void *, void *, int);

void GetMotionOptionNodeBooleanInfoFloatFrameDirectResource(Bool3 *out, char *res, int node)
{
    struct { char pad[0x20]; Bool3 b; char pad2[0xD]; } t __attribute__((aligned(16)));
    func_00033B88(&t, *(char **)(res + 0x1C) + node * 16, *(short *)(res + 4));
    *out = t.b;
}
