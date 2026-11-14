/* Parked: 238 diffs, same size (248 words). Mesh cell initialiser (two passes over rows x cols; each field store re-fetches GetMeshClass). Original keeps the arg regs in a1/s1/s7 and spills the RO_0017D210 pair to sp+0/+8 after the first call; loop variable registers rotate. */
#ifdef NONMATCHING
typedef int Vec4 __attribute__((mode(TI)));
typedef struct {
    char pad0[8];
    int rows;
    int cols;
} Mesh;

typedef struct {
    long lo;
    long hi;
} Pair;

extern Mesh *GetMeshClass(int, long);
extern Pair RO_0017D210;
extern Vec4 ZUnitVector;

#define MESH(a) ((char *)GetMeshClass(a, v.lo))
#define ROWS(a) (*(char **)(MESH(a) + off))
#define PITCH(a) ((GetMeshClass(a, v.lo)->cols << 6) + 0x10)
#define CELL(a, r, c) (ROWS(a) + (r) * PITCH(a) + (c))

void func_0004A3D0(int a1, int a2)
{
    Pair v = RO_0017D210;
    Mesh *m = GetMeshClass(a1, v.lo);
    int pass = 0;
    int off = 0;

    do {
        int r;
        for (r = 0; r < m->rows; r++) {
            int c;
            int cb = 0;
            float fr = (float)r;
            for (c = 0; c < m->cols; c++) {
                if (c == 0 && a2 == 0) {
                    *(float *)(CELL(a1, r, 0) + 0xD0) = fr;
                    *(float *)(CELL(a1, r, 0) + 0xD4) = 0;
                    *(float *)(CELL(a1, r, 0) + 0xD8) = 1.0f;
                    *(float *)(CELL(a1, r, 0) + 0xDC) = 0;
                } else {
                    unsigned int t = c + a2;
                    *(float *)(CELL(a1, r, cb) + 0xD0) = fr;
                    *(float *)(CELL(a1, r, cb) + 0xD4) = 0.99f - (float)(t % 2) * 0.5f;
                    *(float *)(CELL(a1, r, cb) + 0xD8) = 1.0f;
                    *(float *)(CELL(a1, r, cb) + 0xDC) = 0;
                }
                *(Vec4 *)(CELL(a1, r, cb) + 0xE0) = *(Vec4 *)&v;
                *(Vec4 *)(CELL(a1, r, cb) + 0xC0) = ZUnitVector;
                cb += 0x40;
            }
        }
        pass++;
        off += 4;
    } while (pass < 2);
}
#endif
