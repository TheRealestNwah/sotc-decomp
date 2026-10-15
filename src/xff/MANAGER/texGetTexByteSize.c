extern int D_00136280[];

int texGetTexByteSize(int width, int height, int format)
{
    return (width * height >> D_00136280[format * 3]) << 2;
}
