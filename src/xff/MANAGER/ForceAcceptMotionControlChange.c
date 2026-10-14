void ForceAcceptMotionControlChange(char *p, int a)
{
    int v = *(int *)(p + 0x750);

    if (v != a) {
        *(int *)(p + 0x754) = v;
        *(int *)(p + 0x750) = a;
    }
}
