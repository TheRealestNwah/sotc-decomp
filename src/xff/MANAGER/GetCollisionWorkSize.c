#ifdef NONMATCHING /* 38 diffs: register allocation and scheduling; the permuter found nothing better */
typedef struct { int a; int pad[3]; int b; int pad2[31]; } CollElem;
typedef struct { int pad; int count; CollElem *elems; int a; int b; } CollDesc;
extern int GetSizeOfModifiedManagerWork(int);
int GetCollisionWorkSize(CollDesc *d)
{
    int size;
    int i;
    int a;
    int b;
    int n;
    n = d->count;
    size = n * 0x60 + 0x90;
    for (i = 0; i < n; i++) {
        a = d->elems[i].a;
        b = d->elems[i].b;
        size += GetSizeOfModifiedManagerWork(a) + a * 16;
        size += GetSizeOfModifiedManagerWork(a) + a * 16;
        size += GetSizeOfModifiedManagerWork(b) + b * 16;
        size += GetSizeOfModifiedManagerWork(b) + b * 16;
    }
    a = d->a;
    b = d->b;
    size += GetSizeOfModifiedManagerWork(a) + a * 16;
    size += GetSizeOfModifiedManagerWork(a) + a * 16;
    size += GetSizeOfModifiedManagerWork(b) + b * 16;
    size += GetSizeOfModifiedManagerWork(b) + b * 16;
    return size + 0x33;
}
#endif
