static void func_00064A88(void *unused, int value, signed char *p)
{
    if (p[4] != 0) {
        p[3] = 1;
        return;
    }
    if (value == 1) {
        p[2] = value;
    }
}
