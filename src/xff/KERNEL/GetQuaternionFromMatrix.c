typedef int s128 __attribute__((mode(TI)));
extern void iosTransposeMatrix(s128 *, int);
extern void func_0000DD30(int, s128 *);

void GetQuaternionFromMatrix(int q, int m)
{
    s128 t[4];

    iosTransposeMatrix(t, m);
    func_0000DD30(q, t);
}
