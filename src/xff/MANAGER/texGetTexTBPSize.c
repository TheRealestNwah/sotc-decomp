typedef struct { int shift; int b, c; } TF;
extern TF D_00136280[];
int texGetTexTBPSize(int w, int h, int fmt)
{
    int n = w * h >> (D_00136280[fmt].shift + 6);
    return n < 1 ? 1 : n;
}
