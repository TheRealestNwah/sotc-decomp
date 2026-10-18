typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int D_00136F80;
extern int ClipCollisionDirect(void *, Vec4 *, Vec4 *, int);
static inline int clipWideArea(char *state)
{
    Vec4 a, b;
    GetGeometryPointerPosition(&a, state + 0x20);
    GetGeometryPointerPosition(&b, state + 0x60);
    return ClipCollisionDirect(state + 0xA0, &a, &b, D_00136F80);
}
int GetCollisionWideAreaSearch(char *state)
{
    int *counter = (int *)(state + 4);
    if (*(int *)state == 0) {
        if ((*counter)++ > 0) {
            int hit;
            hit = clipWideArea(state);
            *counter = 0;
            *(int *)state = hit ? 2 : 1;
        }
        return *(int *)state;
    }
    return *(int *)state;
}
