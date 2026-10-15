typedef struct { float m[16]; } Mat;
extern void iosCopyMatrix(Mat *, Mat *);

void CopyMultiMatrix(Mat *d, Mat *s, int n)
{
    while (n-- != 0) {
        iosCopyMatrix(d, s);
        d++;
        s++;
    }
}
