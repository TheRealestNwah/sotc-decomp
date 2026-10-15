typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern void setAttainmentObj(char *, int);
extern void setAttainmentObjAndOffset(char *, int, Vec4 *);

void SCRFuncSetAttainPlayer(void *a, float y)
{
    Vec4 o;
    char *w = getSCRDataCtrlWork(a);
    if (y == 0.0f) {
        setAttainmentObj(w, *(int *)(w + 0x4078));
    } else {
        __asm__ __volatile__("sqc2 vf00, 0(%0)" : : "r"(&o) : "memory");
        o.f[1] = y;
        setAttainmentObjAndOffset(w, *(int *)(w + 0x4078), &o);
    }
}
