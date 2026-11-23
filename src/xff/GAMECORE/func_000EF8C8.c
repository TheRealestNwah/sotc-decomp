typedef union { float f; int i; } U;
#define F(p, o) (((U *)((char *)(p) + (o)))->f)
#define B(o) F(out, o) = wa * F(a, o) + wb * F(b, o)
static void func_000EF8C8(char *out, float wa, char *a, float wb, char *b)
{
    B(0xC);
    if (0.0f < F(a, 0x14) && 0.0f < F(b, 0x14) && F(b, 0x14) != 0.001f) B(0x14);
    if (0.0f < F(a, 0x18) && 0.0f < F(b, 0x18) && F(b, 0x18) != 0.001f) B(0x18);
    if (0.0f < F(a, 0x1c) && 0.0f < F(b, 0x1c)) B(0x1c);
    if (0.0f < F(a, 0x28) && 0.0f < F(b, 0x28)) B(0x28);
    B(0x2C);
    B(0x30);
    B(0x34);
    B(0x38);
    B(0x3C);
    B(0x40);
    B(0x44);
    if (0.0f < F(a, 0x4C) && 0.0f < F(b, 0x4C)) B(0x4C);
    B(0x50);
    B(0x54);
    B(0x58);
    B(0x5C);
    B(0x60);
    B(0x64);
    B(0x68);
    B(0x70);
    B(0x74);
    B(0x78);
    B(0x7C);
    B(0x80);
    B(0x84);
    B(0x88);
    B(0x8C);
    B(0x90);
    B(0x94);
    B(0x98);
    B(0x9C);
    B(0xA0);
    B(0xA4);
    if (((U *)(a + 0xA8))->i == 1) {
        B(0xAC);
        B(0xB0);
        B(0xB4);
        B(0xB8);
        B(0xBC);
        B(0xC0);
        B(0xC4);
        B(0xC8);
    }
}
