typedef struct {
    char pad0[0x24];
    int unk24;
    char pad28[0x8];
} BloodWork;

extern float D_0017A9D0;
extern float D_0017A9D4;
extern float D_0017A9D8;
extern int D_0017A9DC;
extern float D_0017A9E0[3];
extern char B_0018A970[];
extern char InitialGeometryPointer[];
extern void *iosMallocAlign(void *, int, int);
extern void CopyGeometryPointer(void *, void *);

BloodWork *effect_blood_init(void *heap, int n, float x, float y, float z, float a, float b, float c)
{
    BloodWork *buf = iosMallocAlign(heap, n * sizeof(BloodWork), 0x10);
    int i;

    D_0017A9DC = n;
    D_0017A9E0[0] = x;
    D_0017A9E0[1] = y;
    D_0017A9E0[2] = z;
    D_0017A9D8 = c;
    D_0017A9D0 = a;
    D_0017A9D4 = b;
    for (i = 0; i < n; i++)
        buf[i].unk24 = 0;
    CopyGeometryPointer(B_0018A970, InitialGeometryPointer);
    return buf;
}
