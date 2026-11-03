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

void SetTRS_Onake_From_ObjectAnimation(TRS *t, Vec4 *a, Vec4 *b, Vec4 *c, float *d)
{
    switch (t->type) {
    case 1:
    case 5:
        t->v10.q = a->q;
        t->v10.q = b->q;
        t->v30.q = c->q;
        t->f40 = d[0];
        break;
    case 45:
        t->v10.q = a->q;
        t->v20.q = b->q;
        t->f50 = d[0];
        break;
    case 3:
        t->v10.q = a->q;
        t->v20.q = c->q;
        break;
    case 12:
        t->v10.q = a->q;
        break;
    case 2:
    case 7:
    case 9:
    case 11:
    case 38:
        t->v10.q = a->q;
        t->v20.q = b->q;
        break;
    case 4:
    case 10:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 32:
    case 48:
        t->v10.q = a->q;
        t->v20.q = b->q;
        t->v30.q = c->q;
        break;
    case 26:
        t->v10.q = b->q;
        t->v20.f.x = c->f.y;
        t->v20.f.z = c->f.w;
        t->v20.f.w = d[0];
        t->v30.f.x = d[1];
        break;
    case 6:
    case 27:
    case 28:
    case 33:
    case 34:
    case 35:
        t->v10.q = a->q;
        t->v20.q = b->q;
        t->v30.f.y = c->f.x;
        t->v30.f.x = c->f.y;
        t->v30.f.z = c->f.w;
        t->v30.f.w = d[0];
        t->f40 = d[1];
        break;
    }
}
