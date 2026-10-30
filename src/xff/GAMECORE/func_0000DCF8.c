typedef struct {
    int count;
    float hist[5][2];
} History;

static void func_0000DCF8(History *h, float a, float b)
{
    int i;

    if (h->count < 5)
        h->count++;
    for (i = h->count - 1; i > 0; i--) {
        h->hist[i][0] = h->hist[i - 1][0];
        h->hist[i][1] = h->hist[i - 1][1];
    }
    h->hist[0][0] = a;
    h->hist[0][1] = b;
}
