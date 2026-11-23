typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    struct {
        float x, y, z, w;
    } f;
} Vec4;

typedef struct {
    int type;
    int pad[3];
    Vec4 v10;
    Vec4 v20;
    Vec4 v30;
    float f40;
    float f44[3];
    float f50;
} TRS;

extern Vec4 All1Vector;

void GetTRS_Onake_From_ObjectAnimation(TRS *t, Vec4 *a, Vec4 *b, Vec4 *c, Vec4 *d)
{
    switch (t->type) {
    case 1:
    case 5:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->f40;
        break;
    case 2:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 45:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->f50;
        break;
    case 11:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 3:
        a->q = t->v10.q;
        __asm__ __volatile__("sqc2 $vf0, 0x0(%0)" : : "r"(b) : "memory");
        c->q = t->v20.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 10:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 4:
    case 48:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 7:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 12:
        a->q = t->v10.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(b) : "memory");
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 6:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    case 9:
    case 38:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = All1Vector.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 14:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 15:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 16:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 18:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 19:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 20:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 21:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 17:
    case 32:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 22:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 23:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 24:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 25:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->q = t->v30.q;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        break;
    case 26:
        b->q = t->v10.q;
        c->f.y = t->v20.f.x;
        c->f.w = t->v20.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v20.f.w;
        d->f.y = t->v30.f.x;
        break;
    case 27:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    case 28:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    case 33:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    case 34:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    case 35:
        a->q = t->v10.q;
        b->q = t->v20.q;
        c->f.x = t->v30.f.y;
        c->f.y = t->v30.f.x;
        c->f.w = t->v30.f.z;
        __asm__ __volatile__("sq $0, 0(%0)" : : "r"(d) : "memory");
        d->f.x = t->v30.f.w;
        d->f.y = t->f40;
        break;
    }
}
