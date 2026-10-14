extern float D_0012FDE0;
extern int D_0012FDE4;
extern float D_0012FDE8;
extern unsigned char padManagerData[1];

void doit_debug_utility(float fparg0)
{
    D_0012FDE0 = fparg0;
    if ((*(int *)((char *)(&padManagerData) + 0xFA0)) & 0x800) {
        D_0012FDE8 = 2.0f;
        D_0012FDE4 = D_0012FDE4 == 0;
        return;
    }
    D_0012FDE8 -= fparg0;
}
