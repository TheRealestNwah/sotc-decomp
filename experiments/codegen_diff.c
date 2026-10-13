typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec;

extern int ext(int);
extern float extf(float);
static int helper(int a) { return a * 7 + (a >> 3); }

int loop_sum(int *p, int n)
{
    int i, s = 0;
    for (i = 0; i < n; i++) s += p[i] * p[i];
    return s;
}

int switch_dense(int k)
{
    switch (k) {
    case 0: return ext(1);
    case 1: return ext(5) + 2;
    case 2: return 9;
    case 3: return ext(k) * 3;
    case 5: return -1;
    default: return k;
    }
}

float vec_len2(Vec *v) { return v->x * v->x + v->y * v->y + v->z * v->z; }

void vec_lerp(Vec *o, Vec *a, Vec *b, float t)
{
    o->x = a->x + (b->x - a->x) * t;
    o->y = a->y + (b->y - a->y) * t;
    o->z = a->z + (b->z - a->z) * t;
    o->w = 1.0f;
}

long long mul64(long long a, long long b) { return a * b + (a >> 7); }

int divmod(int a, int b) { return a / b + a % b; }

unsigned udiv_const(unsigned a) { return a / 10 + a % 3; }

int calls_static(int a) { return helper(a) + helper(a + 1); }

float clampf(float v, float lo, float hi) { return v < lo ? lo : v > hi ? hi : v; }

int nested(int *a, int n, int m)
{
    int i, j, c = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (a[i * m + j] > i) c += ext(j);
    return c;
}

void copy128(u_long128 *d, u_long128 *s, int n)
{
    while (n-- > 0) *d++ = *s++;
}

int bitfield_ops(unsigned x) { return ((x >> 4) & 0xF) | ((x & 3) << 12) | (x ^ 0x5555); }

float call_float(float a) { return extf(a * 2.0f) + extf(a - 0.5f) * 3.25f; }

int many_args(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
    return ext(a + b) + c * d - e + f * g + h - i * j;
}
