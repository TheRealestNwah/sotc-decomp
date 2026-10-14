extern int B_001482A0[];

void glPopMatrix(void)
{
    int *p = B_001482A0;
    int n = *p - 1;

    if (n < 0) {
        n = 0;
    }
    *p = n;
}
