#define NULL ((void *)0)
extern void func_000317C8(void *);
extern void *B_00189DF4;

void allArrowRelease(void)
{
    void *temp_s0;
    void *var_a0;

    var_a0 = B_00189DF4;
    if (var_a0 != NULL) {
        do {
            temp_s0 = (*(void **)((char *)(var_a0) + 0xC0));
            func_000317C8(var_a0);
            var_a0 = temp_s0;
        } while (var_a0 != NULL);
    }
}
