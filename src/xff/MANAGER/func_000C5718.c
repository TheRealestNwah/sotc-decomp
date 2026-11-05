extern char RO_0011A908[];
extern void *get_fast_get_malloc_partition(void);
extern void *malloc_from_src_partition(void *, int, char *, int);
extern void func_000C5A50(char *, int, int, int, int, int);

static inline float distSq(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

#ifdef NONMATCHING
/* 77 diffs: register allocation (head/t1 saved registers swapped, cur not copied from a temporary) */
static char *func_000C5718(char **head, void *pos, char *def, int a3, int t0, int t1, int t2)
{
    char *ret;
    char *cur;
    char *prev;
    char *node;
    int id;

    cur = *head;
    ret = 0;
    if (cur == 0)
        goto end;
    id = *(int *)(def + 0x2C);
    if (id == 0)
        goto end;
    if (id != *(int *)(*(char **)cur + 0x2C))
        goto end;
    if (!(distSq(pos, cur + 0x20) <= *(float *)(def + 0x30) * *(float *)(def + 0x30)))
        goto end;
    prev = 0;
    goto test;
next:
    prev = cur;
    cur = *(char **)(cur + 0x1B0);
    if (cur != 0)
        goto test;
    node = malloc_from_src_partition(get_fast_get_malloc_partition(), 0x1C0, RO_0011A908, 1);
    if (node != 0) {
        *(char **)node = def;
        func_000C5A50(node + 0x10, a3, t0, t1, t2, *(int *)(def + 0x48));
        *(char **)(node + 0x1B0) = 0;
    }
    ret = node;
    *(char **)(prev + 0x1B0) = ret;
    goto end;
test:
    if (!(*(int *)(def + 0x34) < *(int *)(*(char **)cur + 0x34)))
        goto next;
    node = malloc_from_src_partition(get_fast_get_malloc_partition(), 0x1C0, RO_0011A908, 1);
    if (node != 0) {
        *(char **)node = def;
        func_000C5A50(node + 0x10, a3, t0, t1, t2, *(int *)(def + 0x48));
        *(char **)(node + 0x1B0) = 0;
    }
    ret = node;
    if (ret == 0)
        goto end;
    if (prev == 0)
        *head = ret;
    else
        *(char **)(prev + 0x1B0) = ret;
    *(char **)(node + 0x1B0) = cur;
end:
    return ret;
}
#endif
