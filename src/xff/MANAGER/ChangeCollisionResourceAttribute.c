typedef struct { unsigned long attr; long pad; } CollAttr;
typedef struct { char pad[0x30]; int n; CollAttr *a; } CollRes;

void ChangeCollisionResourceAttribute(CollRes *r, unsigned long m1, unsigned long v1, unsigned long m2, unsigned long v2,
                                      unsigned long clr, unsigned long set)
{
    int i = r->n;
    CollAttr *p = r->a;
    while (--i != -1) {
        unsigned long v = p->attr;
        if ((v & m1) == v1 && (v & m2) == v2)
            p->attr = (v & ~clr) | set;
        p++;
    }
}
