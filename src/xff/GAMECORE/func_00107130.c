extern void _resetBaseMoveWork(int a, char *p);
extern void func_001071B0(char *);

static const union {
    int i;
    float f;
} RO_001814BC = {0x7FFFFFFF};

static void func_00107130(int a, char *p)
{
    _resetBaseMoveWork(a, p);
    *(float *)(p + 0x50) = RO_001814BC.f;
    *(int *)(p + 0x114) = 0;
    *(int *)(p + 0x34) = 0;
    *(int *)(p + 0x30) = 1;
    *(int *)(p + 0x38) = 0;
    *(int *)(p + 0x3C) = 0;
    *(int *)(p + 0x40) = 0;
    *(int *)(p + 0x44) = 1;
    *(int *)(p + 0xF0) = 0;
    *(int *)(p + 0x48) = 1;
    *(float *)(p + 0x4C) = 3.14159251f;
    *(float *)(p + 0x110) = 1.0f;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(p + 0x120) : "memory");
    func_001071B0(p);
}
