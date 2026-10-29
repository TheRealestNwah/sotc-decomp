extern void func_0007E298();
extern void *_isysCreateObj(void *, int, int, int, int, int);

unsigned char *CreateAmbientLightObj(void *heap, int extra, int *col)
{
    unsigned char *o = _isysCreateObj(heap, 0x14, 0x28, extra, (int)func_0007E298, 0x10);
    int *l;
    if (o != 0) {
        l = o[8] != 0x14 ? 0 : (int *)(o + 0x1C);
        l[0] = col[0];
        l[1] = col[1];
        l[2] = col[2];
    }
    return o;
}
