typedef struct {
    int count;
    char a[0x48];
    char b[0x194];
    char c[0xCC];
    char d[0x84];
    char e[0xD0];
    char f[0xE4];
    char g[0xE4];
    char h[0x8C];
} Tables;

extern void *memset(void *, int, unsigned int);

static void func_000ED5D8(Tables *t)
{
    t->count = 0;
    memset(t->a, 0, sizeof(t->a));
    memset(t->b, 0, sizeof(t->b));
    memset(t->c, 0, sizeof(t->c));
    memset(t->d, 0, sizeof(t->d));
    memset(t->e, 0, sizeof(t->e));
    memset(t->f, 0, sizeof(t->f));
    memset(t->g, 0, sizeof(t->g));
    memset(t->h, 0, sizeof(t->h));
}
