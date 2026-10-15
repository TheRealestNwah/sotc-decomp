extern void (*D_00040BB8)(void);
extern volatile int D_00040BA0;

void iFinish(void)
{
    if (D_00040BB8 != 0)
        D_00040BB8();
    D_00040BA0 = 1;
}
