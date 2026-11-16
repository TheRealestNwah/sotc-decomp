/* Parked: 182 diffs with per-file -fno-gcse (210 without), same size (229 words). Fresh re-draft: the function takes three arguments (the first, in $a0, is unused; a1/a2 arrive in $a1/$a2), GetMeshClass takes one argument (the old draft passed the pair's low word; the ld/sd of RO_0017D210 is just the 16-byte copy to sp+0), and the pair is copied high word first. Body structure now lines up. Remaining: original keeps pass at sp+0x10 starting from 0 (ours folds it to start at 1), per-row copy of off in s2, and register numbering (a1/a2/m/c/cb in s1/s7/s6/s5/s4). */
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

extern Mesh *GetMeshClass(int);
extern Pair RO_0017D210;
extern Vec4 ZUnitVector;

#define MESH(a) ((char *)GetMeshClass(a))
#define ROWS(a) (*(char **)(MESH(a) + off))
#define PITCH(a) ((GetMeshClass(a)->cols << 6) + 0x10)
#define CELL(a, r, c) (ROWS(a) + (r) * PITCH(a) + (c))

void func_0004A3D0(int unused, int a1, int a2)
{
    Pair v;
    Mesh *m;
    int pass = 0;
    int off = 0;

    v.hi = RO_0017D210.hi;
    v.lo = RO_0017D210.lo;
    m = GetMeshClass(a1);

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
