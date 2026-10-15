extern long B_0004E590;

void iosCdStSectorAlignSkip(void)
{
    int r = B_0004E590 % 2048;
    if (r != 0)
        B_0004E590 += (unsigned int)(2048 - r);
}
