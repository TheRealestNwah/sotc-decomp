extern int iosFree();

int vramDeleteBlock(int a, int b, int c, int d)
{
    return iosFree(a, b, c, d);
}
