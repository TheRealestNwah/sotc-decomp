typedef struct {
    float m[16];
} Matrix;

extern int B_001482A0;
extern Matrix B_00147AA0[];
extern void iosCopyMatrix(void *, void *);

void glGetCurrentMatrix(void *m)
{
    iosCopyMatrix(m, &B_00147AA0[B_001482A0]);
}
