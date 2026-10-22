extern int texGetTexTBPSize(int, int, int);
static void *func_000305B8(void *, int);
void *vramAlloc(void *context, int format, int width, int height, int levels)
{
    int total = 0;
    int i;
    for (i = 0; i < levels; ++i)
        total += texGetTexTBPSize(width >> i, height >> i, format);
    return func_000305B8(context, total);
}
