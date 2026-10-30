typedef struct {
    long words[8];
} Block64;

typedef struct {
    Block64 block;
    int a;
    int b;
} Snapshot;

extern Block64 *B_001502E0;
extern int B_001502E4;
extern int B_001502E8;

static void func_000DDD78(char *p)
{
    Snapshot *dst = *(Snapshot **)(p + 0x48);
    dst->block = *B_001502E0;
    dst->a = B_001502E8;
    dst->b = B_001502E4;
}
