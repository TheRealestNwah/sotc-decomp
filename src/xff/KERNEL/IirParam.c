extern void func_0002FA10(char *);
extern void func_0002FB10(char *);
extern void func_0002FC10(char *);
extern void func_0002FD38(char *);
extern void func_0002FF00(char *);

void IirParam(char *p, int type, float freq, float gain)
{
    float a0;

    *(float *)(p + 0x30) = freq;
    *(float *)(p + 0x2C) = gain;
    *(int *)p = type;
    switch (type) {
    case 5:
        func_0002FC10(p);
        break;
    case 3:
        func_0002FD38(p);
        break;
    case 4:
        func_0002FF00(p);
        break;
    case 1:
        func_0002FA10(p);
        break;
    case 2:
        func_0002FB10(p);
        break;
    }
    a0 = *(float *)(p + 0x4);
    *(float *)(p + 0x34) = *(float *)(p + 0x10) / a0;
    *(float *)(p + 0x38) = *(float *)(p + 0x14) / a0;
    *(float *)(p + 0x3C) = *(float *)(p + 0x18) / a0;
    *(float *)(p + 0x40) = *(float *)(p + 0x8) / a0;
    *(float *)(p + 0x44) = *(float *)(p + 0xC) / a0;
}
