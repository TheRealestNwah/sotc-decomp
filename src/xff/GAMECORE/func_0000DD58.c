typedef struct {
    float a;
    float b;
} Pair;

typedef struct {
    union { int n; float f; } u;
    Pair p[1];
} PairList;

static void func_0000DD58(float *outA, float *outB, PairList *list)
{
    float a = 0.0f;
    float b = 0.0f;
    int n = list->u.n;
    int i;
    Pair *p;

    if (n > 0) {
        p = list->p;
        for (i = n; i != 0; i--) {
            a += p->a;
            b += p->b;
            p++;
        }
    }
    *outA = a / n;
    *outB = b / list->u.n;
}
