typedef struct { float m[16]; } Mat;
extern int B_001482A0;
extern Mat B_00147AA0[];
extern void iosCopyMatrix(Mat *, Mat *);

void glPushMatrix(void)
{
    int *p = &B_001482A0;
    int n = *p + 1;
    *p = n;
    if (n >= 32) {
        *p = 32;
        return;
    }
    iosCopyMatrix(&B_00147AA0[n], &B_00147AA0[n - 1]);
}
