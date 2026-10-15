typedef struct { char pad[0x18]; } AttrSt;
extern AttrSt B_0018B748[];
static int func_00090560(AttrSt *, int, int, int, int);

int attrStatusUpdate(int a, int b, int c)
{
    int r = 0;
    AttrSt *p = B_0018B748;
    int i = 4;
    do {
        r = func_00090560(p++, a, b, r, c);
    } while (--i);
    return r;
}
