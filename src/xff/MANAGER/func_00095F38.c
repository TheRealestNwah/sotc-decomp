typedef struct {
    unsigned int w0;
    unsigned int a : 9;
    unsigned int b : 2;
    unsigned int c : 10;
    unsigned int d : 10;
    unsigned int e : 1;
} Hdr34;

typedef struct {
    int pad0;
    float f4;
} Q;

typedef struct {
    Q *q;
    int pad4;
    unsigned int w8;
    void *wC;
    float f10;
} Val;

typedef struct {
    int pad0[4];
    unsigned int flags;
} Res;

typedef struct {
    Res *res;
    Val *val;
    int pad8[2];
    float f10;
    int pad14[2];
} Ent;

typedef struct {
    char pad0[4];
    unsigned int ents;
    unsigned int w8;
    char padC[0x28];
    Hdr34 h34;
} Obj;

#define CNT(o) ((int)(((o)->w8 >> 4) & 0x3FF))

static void func_00095F38(Obj *o, int n)
{
    Hdr34 *h = &o->h34;
    int i;

    if (n >= 0) {
        h->a = n + 1;
    } else {
        h->a = 0;
    }
    h->w0 = 0;
    h->b = 0;
    h->c = 0;
    h->d = 0;
    i = 0;
    if (CNT(o) != 0) {
        do {
            Ent *e = (Ent *)o->ents + i;
            Val *p = e->val;
            Res *r = e->res;
            if (p != 0) {
                Q *q = p->q;
                if (q != 0 && !(r->flags & 4)) {
                    p->wC = 0;
                    p->w8 = (p->w8 & 0x87FFFFFF) | 0x08000000;
                    p->f10 = q->f4;
                } else {
                    float f = 0.0f;
                    if (q != 0) f = q->f4;
                    p->f10 = f;
                    p->wC = 0;
                    p->w8 = (p->w8 & 0x87FFFFFF) | 0x08000000;
                }
            } else {
                e->f10 = 1.0f;
            }
            i++;
        } while (i < (int)(((volatile Obj *)o)->w8 >> 4 & 0x3FF));
    }
}
