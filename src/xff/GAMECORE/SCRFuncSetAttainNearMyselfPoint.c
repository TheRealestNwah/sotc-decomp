typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void getNearPointPosUserPathWork(char *, Vec4 *, int, int, int);
extern void setAttainmentPos(char *, Vec4 *);

void SCRFuncSetAttainNearMyselfPoint(void *a, float dy)
{
    Vec4 p;
    char *w = getSCRDataCtrlWork(a);
    p.q = (*(Vec4 **)(GetLayoutClass(a) + 0x134))->q;
    getNearPointPosUserPathWork(w, &p, *(int *)(GetLayoutClass(a) + 0x134), 1, -1);
    p.f[1] += dy;
    setAttainmentPos(w, &p);
}
