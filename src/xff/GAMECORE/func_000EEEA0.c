#define F(p, o) (*(float *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))

static void func_000EEEA0(char *o, float wa, char *a, float wb, char *b)
{
    if (0.0f < F(a, 0x1C) && 0.0f < F(b, 0x1C))
        F(o, 0x1C) = wa * F(a, 0x1C) + wb * F(b, 0x1C);
    if (0.0f < F(a, 0x20) && 0.0f < F(b, 0x20))
        F(o, 0x20) = wa * F(a, 0x20) + wb * F(b, 0x20);
    if (0.0f < F(a, 0x24) && 0.0f < F(b, 0x24))
        F(o, 0x24) = wa * F(a, 0x24) + wb * F(b, 0x24);
    F(o, 0x28) = wa * F(a, 0x28) + wb * F(b, 0x28);
    F(o, 0x34) = wa * F(a, 0x34) + wb * F(b, 0x34);
    F(o, 0x38) = wa * F(a, 0x38) + wb * F(b, 0x38);
    F(o, 0x3C) = wa * F(a, 0x3C) + wb * F(b, 0x3C);
    F(o, 0x40) = wa * F(a, 0x40) + wb * F(b, 0x40);
    if (0.0f < F(a, 0x44) && 0.0f < F(b, 0x44))
        F(o, 0x44) = wa * F(a, 0x44) + wb * F(b, 0x44);
    if (0.0f < F(a, 0x48) && 0.0f < F(b, 0x48))
        F(o, 0x48) = wa * F(a, 0x48) + wb * F(b, 0x48);
    F(o, 0x4C) = wa * F(a, 0x4C) + wb * F(b, 0x4C);
    F(o, 0x50) = wa * F(a, 0x50) + wb * F(b, 0x50);
    F(o, 0x54) = wa * F(a, 0x54) + wb * F(b, 0x54);
    F(o, 0x58) = wa * F(a, 0x58) + wb * F(b, 0x58);
    F(o, 0x5C) = wa * F(a, 0x5C) + wb * F(b, 0x5C);
    F(o, 0x60) = wa * F(a, 0x60) + wb * F(b, 0x60);
    F(o, 0x64) = wa * F(a, 0x64) + wb * F(b, 0x64);
    F(o, 0x68) = wa * F(a, 0x68) + wb * F(b, 0x68);
    F(o, 0x6C) = wa * F(a, 0x6C) + wb * F(b, 0x6C);
    if (0.0f < F(a, 0x70) && 0.0f < F(b, 0x70))
        F(o, 0x70) = wa * F(a, 0x70) + wb * F(b, 0x70);
    if (0.0f < F(a, 0x74) && 0.0f < F(b, 0x74))
        F(o, 0x74) = wa * F(a, 0x74) + wb * F(b, 0x74);
    F(o, 0x78) = wa * F(a, 0x78) + wb * F(b, 0x78);
    if (0.0f < F(a, 0x7C) && 0.0f < F(b, 0x7C))
        F(o, 0x7C) = wa * F(a, 0x7C) + wb * F(b, 0x7C);
    F(o, 0x80) = wa * F(a, 0x80) + wb * F(b, 0x80);
    F(o, 0x84) = wa * F(a, 0x84) + wb * F(b, 0x84);
    F(o, 0x88) = wa * F(a, 0x88) + wb * F(b, 0x88);
    F(o, 0xAC) = wa * F(a, 0xAC) + wb * F(b, 0xAC);
    F(o, 0xB0) = wa * F(a, 0xB0) + wb * F(b, 0xB0);
    if (0.0f < F(a, 0xB8) && 0.0f < F(b, 0xB8))
        F(o, 0xB8) = wa * F(a, 0xB8) + wb * F(b, 0xB8);
    if (0.0f < F(a, 0xBC) && 0.0f < F(b, 0xBC))
        F(o, 0xBC) = wa * F(a, 0xBC) + wb * F(b, 0xBC);
    if (0.0f < F(a, 0xC0) && 0.0f < F(b, 0xC0))
        F(o, 0xC0) = wa * F(a, 0xC0) + wb * F(b, 0xC0);
    if (0.0f < F(a, 0xC4) && 0.0f < F(b, 0xC4))
        F(o, 0xC4) = wa * F(a, 0xC4) + wb * F(b, 0xC4);
    if (0.0f < F(a, 0xD4) && 0.0f < F(b, 0xD4))
        F(o, 0xD4) = wa * F(a, 0xD4) + wb * F(b, 0xD4);
    if (0.0f < F(a, 0xD8) && 0.0f < F(b, 0xD8))
        F(o, 0xD8) = wa * F(a, 0xD8) + wb * F(b, 0xD8);
    if (0.0f < F(a, 0xDC) && 0.0f < F(b, 0xDC))
        F(o, 0xDC) = wa * F(a, 0xDC) + wb * F(b, 0xDC);
    F(o, 0xE0) = wa * F(a, 0xE0) + wb * F(b, 0xE0);
    F(o, 0xE4) = wa * F(a, 0xE4) + wb * F(b, 0xE4);
    F(o, 0xEC) = wa * F(a, 0xEC) + wb * F(b, 0xEC);
    F(o, 0xF0) = wa * F(a, 0xF0) + wb * F(b, 0xF0);
    F(o, 0xF4) = wa * F(a, 0xF4) + wb * F(b, 0xF4);
    F(o, 0xF8) = wa * F(a, 0xF8) + wb * F(b, 0xF8);
    F(o, 0x100) = wa * F(a, 0x100) + wb * F(b, 0x100);
    F(o, 0x104) = wa * F(a, 0x104) + wb * F(b, 0x104);
    F(o, 0x108) = wa * F(a, 0x108) + wb * F(b, 0x108);
    F(o, 0x10C) = wa * F(a, 0x10C) + wb * F(b, 0x10C);
    F(o, 0x110) = wa * F(a, 0x110) + wb * F(b, 0x110);
    if (0.0f < F(a, 0x11C) && 0.0f < F(b, 0x11C))
        F(o, 0x11C) = wa * F(a, 0x11C) + wb * F(b, 0x11C);
    if (0.0f < F(a, 0x120) && 0.0f < F(b, 0x120))
        F(o, 0x120) = wa * F(a, 0x120) + wb * F(b, 0x120);
    if (0.0f < F(a, 0x124) && 0.0f < F(b, 0x124))
        F(o, 0x124) = wa * F(a, 0x124) + wb * F(b, 0x124);
    F(o, 0x128) = wa * F(a, 0x128) + wb * F(b, 0x128);
    F(o, 0x12C) = wa * F(a, 0x12C) + wb * F(b, 0x12C);
    F(o, 0x130) = wa * F(a, 0x130) + wb * F(b, 0x130);
    F(o, 0x134) = wa * F(a, 0x134) + wb * F(b, 0x134);
    F(o, 0x138) = wa * F(a, 0x138) + wb * F(b, 0x138);
    F(o, 0x13C) = wa * F(a, 0x13C) + wb * F(b, 0x13C);
    if (0.0f < F(a, 0x144) && 0.0f < F(b, 0x144))
        F(o, 0x144) = wa * F(a, 0x144) + wb * F(b, 0x144);
    if (0.0f < F(a, 0x148) && 0.0f < F(b, 0x148))
        F(o, 0x148) = wa * F(a, 0x148) + wb * F(b, 0x148);
    if (0.0f < F(a, 0x14C) && 0.0f < F(b, 0x14C))
        F(o, 0x14C) = wa * F(a, 0x14C) + wb * F(b, 0x14C);
    if (I(b, 0x140) == 1)
        F(o, 0x150) = F(a, 0x150);
    else
        F(o, 0x150) = wa * F(a, 0x150) + wb * F(b, 0x150);
    if (0.0f < F(a, 0x154) && 0.0f < F(b, 0x154))
        F(o, 0x154) = wa * F(a, 0x154) + wb * F(b, 0x154);
    if (0.0f < F(a, 0x158) && 0.0f < F(b, 0x158))
        F(o, 0x158) = wa * F(a, 0x158) + wb * F(b, 0x158);
    if (0.0f < F(a, 0x15C) && 0.0f < F(b, 0x15C))
        F(o, 0x15C) = wa * F(a, 0x15C) + wb * F(b, 0x15C);
    F(o, 0x160) = wa * F(a, 0x160) + wb * F(b, 0x160);
    F(o, 0x164) = wa * F(a, 0x164) + wb * F(b, 0x164);
    F(o, 0x170) = wa * F(a, 0x170) + wb * F(b, 0x170);
    if (0.0f < F(a, 0x174) && 0.0f < F(b, 0x174))
        F(o, 0x174) = wa * F(a, 0x174) + wb * F(b, 0x174);
    if (0.0f < F(a, 0x178) && 0.0f < F(b, 0x178))
        F(o, 0x178) = wa * F(a, 0x178) + wb * F(b, 0x178);
    if (0.0f < F(a, 0x17C) && 0.0f < F(b, 0x17C))
        F(o, 0x17C) = wa * F(a, 0x17C) + wb * F(b, 0x17C);
    if (0.0f < F(a, 0x180) && 0.0f < F(b, 0x180))
        F(o, 0x180) = wa * F(a, 0x180) + wb * F(b, 0x180);
    if (0.0f < F(a, 0x184) && 0.0f < F(b, 0x184))
        F(o, 0x184) = wa * F(a, 0x184) + wb * F(b, 0x184);
    if (0.0f < F(a, 0x188) && 0.0f < F(b, 0x188))
        F(o, 0x188) = wa * F(a, 0x188) + wb * F(b, 0x188);
    F(o, 0x18C) = wa * F(a, 0x18C) + wb * F(b, 0x18C);
}
