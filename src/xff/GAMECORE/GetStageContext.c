#define NULL ((void *)0)
typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 packed;
    volatile float components[4];
} Vector;

typedef struct {
    char name[4];
    const Vector *position;
    int offsetX;
    int offsetZ;
    int width;
    int depth;
    volatile int x;
    volatile int z;
    int area;
    int part;
    char pad28[8];
    Vector center;
} StageContext;

typedef struct {
    char pad0[0x14];
    float width;
    float depth;
    char pad1C[0x18];
    int columns;
    int rows;
} StageGrid;

/* This view preserves the original reloads after context stores. */
typedef union {
    StageGrid *grid;
    int raw;
} GridAddress;
extern GridAddress D_0017A868;
extern void *D_0017A86C;
extern unsigned char RO_0017CE20[3];
extern char RO_0017CE28[];
extern Vector ZeroPoint;
extern void iosSPrintf(char *, const char *, ...);
int GetStageContext(StageContext *);


/* These alias and volatile views are matching aids; types remain provisional. */
#ifdef NONMATCHING
int GetStageContext(StageContext *arg0)
{
    unsigned char name2;
    unsigned short name0;
    const Vector *temp_t2;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f1_4;
    int temp_a0;
    int temp_a0_2;
    int temp_a1;
    int temp_a2;
    int temp_a3;
    int temp_a3_2;
    int temp_f0;
    int temp_f1;
    int temp_f1_2;
    int temp_f1_3;
    int temp_lo;
    int temp_lo_2;
    int var_t3;
    int var_v0;

    name2 = RO_0017CE20[2];
    name0 = *(unsigned short *)RO_0017CE20;
    arg0->name[2] = name2;
    *(unsigned short *)arg0 = name0;
    arg0->center.packed = ZeroPoint.packed;
    if (D_0017A868.grid != NULL) {
        var_t3 = 2;
        if (D_0017A86C != NULL) {
            temp_t2 = arg0->position;
            temp_f1 = (int) ((D_0017A868.grid->width * (float) D_0017A868.grid->columns * 0.5f) - temp_t2->components[0]);
            arg0->offsetX = temp_f1;
            temp_f0 = (int) (temp_t2->components[2] + (D_0017A868.grid->depth * (float) D_0017A868.grid->rows * 0.5f));
            arg0->offsetZ = temp_f0;
            temp_f1_2 = (int) D_0017A868.grid->width;
            temp_lo = temp_f1 / temp_f1_2;
            arg0->width = temp_f1_2;
            temp_f1_3 = (int) D_0017A868.grid->depth;
            arg0->depth = temp_f1_3;
            temp_lo_2 = temp_f0 / temp_f1_3;
            arg0->x = temp_lo;
            temp_a1 = (temp_lo < 0) ? 0 : temp_lo;
            arg0->x = temp_a1;
            temp_a2 = (temp_lo_2 < 0) ? 0 : temp_lo_2;
            arg0->z = temp_a2;
            temp_a3 = D_0017A868.grid->columns - 1;
            temp_a3_2 = (temp_a1 < temp_a3) ? temp_a1 : temp_a3;
            arg0->x = temp_a3_2;
            temp_a0 = D_0017A868.grid->rows - 1;
            temp_a0_2 = (temp_a2 < temp_a0) ? temp_a2 : temp_a0;
            arg0->z = temp_a0_2;
            temp_f0_2 = D_0017A868.grid->width;
            arg0->center.components[0] = (temp_f0_2 * (float) D_0017A868.grid->columns * 0.5f) - (((float) temp_a3_2 * temp_f0_2) + (temp_f0_2 * 0.5f));
            temp_f0_3 = D_0017A868.grid->depth;
            temp_f1_4 = (((float) temp_a0_2 * temp_f0_3) + (temp_f0_3 * 0.5f)) - (temp_f0_3 * (float) D_0017A868.grid->rows * 0.5f);
            arg0->center.components[2] = temp_f1_4;
            arg0->area = (temp_a0_2 * D_0017A868.grid->columns) + temp_a3_2;
            if (!(temp_f1_4 < temp_t2->components[2])) {
                var_t3 = 0;
            }
            var_v0 = 1;
            if (!(temp_t2->components[0] < arg0->center.components[0])) {
                var_v0 = 0;
            }
            arg0->part = var_v0 + var_t3;
            iosSPrintf(arg0->name, RO_0017CE28, arg0->x + 0x41, arg0->z);
            return 1;
        }
    }
    return 0;
}
#endif
