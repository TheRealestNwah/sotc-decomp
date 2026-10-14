typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
void InitDamageClass(char *p)
{
    *(int *)(p + 0x54)=-1;
    *(int *)(p + 0x58)=0;
    *(int *)p=0;
    *(int *)(p + 0x5C)=0;
    *(int *)(p + 0x60)=-1;
    *(int *)(p + 0x6C)=-1;
    *(int *)(p + 0x64)=0;
    *(int *)(p + 0x68)=0;
    *(s128 *)(p + 0x80)=ZeroPoint;
    *(int *)(p + 0x90)=0;
    *(int *)(p + 0x70)=0;
    *(int *)(p + 0x94)=0;
}
