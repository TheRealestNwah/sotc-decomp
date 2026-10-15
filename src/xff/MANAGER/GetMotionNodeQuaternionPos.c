extern void func_00031210(void *, void *, int, int, int, int);
extern void ExchangeLWQuaternion(void *, void *);

void GetMotionNodeQuaternionPos(void *q, void *b, int c, int d, int e)
{
    func_00031210(q, b, 0, c, d, e);
    ExchangeLWQuaternion(q, q);
}
