typedef union { long words[2]; int i[4]; } IVector;
/* iosMulMvec: component-wise integer-vector multiplication. */
static void func_0000D548(IVector *, const IVector *, const IVector *);
int iosCalcIcolorToBrightness(unsigned int color)
{
    IVector channels;

    channels.i[0] = color & 0xFF;
    channels.i[1] = (color >> 8) & 0xFF;
    channels.i[2] = (color >> 16) & 0xFF;
    channels.i[3] = color >> 24;
    {
        IVector factors = { .i = {0x266666, 0x4B851E, 0xE147A, 0x7FFFFFFF} };
        func_0000D548(&channels, &channels, &factors);
    }
    return ((channels.i[0] + channels.i[1] + channels.i[2]) >> 23) & 0xFF;
}
