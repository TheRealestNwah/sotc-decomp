typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern int getPointPosFromEvent(char *, int, Vec4 *);
extern void setAttainmentPos(char *, Vec4 *);

void SCRFuncSetAttainPointPosForEventID(void *a, int id)
{
    Vec4 p;
    char *w = getSCRDataCtrlWork(a);
    if (getPointPosFromEvent(w, id, &p))
        setAttainmentPos(w, &p);
}
