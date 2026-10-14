extern unsigned char B_0018A6C0[1];

int effectGetDamageWork(void **arg0)
{
    *arg0 = &B_0018A6C0;
    return (*(int *)((char *)(&B_0018A6C0) + 0x2A8));
}
