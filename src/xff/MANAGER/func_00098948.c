#ifdef NONMATCHING /* first case branch should be beql with the def load in its delay slot */
typedef struct { int *p; int pad; unsigned int state : 4; } Obj;
extern void func_00093880(Obj *, int);
static void func_00098948(Obj *o)
{
    switch (o->state) {
    case 1:
        func_00093880(o, o->p[3]);
        o->state = 2;
        break;
    case 4:
        func_00093880(o, o->p[3]);
        o->state = 5;
        break;
    }
}
#endif
