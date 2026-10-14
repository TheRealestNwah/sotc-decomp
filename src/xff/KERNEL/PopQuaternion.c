extern int D_000409B0[];

void PopQuaternion(void)
{
    int *p = D_000409B0;
    int n = *p - 1;

    if (n < 0) {
        n = 0;
    }
    *p = n;
}
