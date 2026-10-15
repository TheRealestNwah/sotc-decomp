typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern int getPointPosFromEvent(char *, int, Vec4 *);
extern void setAttainmentPos(char *, Vec4 *);

void SCRFuncSetAttainPointPosForLanding(void *a, int ev)
{
    Vec4 p;
    char *w = getSCRDataCtrlWork(a);
    int m = *(int *)(w + 0x4090);
    if (m == 2 || m == 4) {
        if (getPointPosFromEvent(w, ev, &p))
            setAttainmentPos(w, &p);
    }
}
