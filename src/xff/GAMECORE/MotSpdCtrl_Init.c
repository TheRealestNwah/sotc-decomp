extern void MotSpdCtrl_Reset(char *);

void MotSpdCtrl_Init(char *p, int a)
{
    MotSpdCtrl_Reset(p);
    *(int *)(p + 0x14) = a;
}
