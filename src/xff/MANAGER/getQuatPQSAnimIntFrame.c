extern void T_00031438(void *, int, int, void *);
void getQuatPQSAnimIntFrame(void *a, unsigned char *b, void *c)
{
    int v = *(int *)(b + 8);
    int k = b[1];
    if (v != 0)
        T_00031438(a, k, v, c);
}
