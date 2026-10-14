typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern void setAttainmentPos(void *, Vec4 *);

void SCRFuncSetAttainLostPlayerPosGlobalY(void *actor, float y)
{
    char *w = getSCRDataCtrlWork(actor);
    Vec4 t;
    t.q = ((Vec4 *)(w + 0x4030))->q;
    t.f[1] = y;
    setAttainmentPos(w, &t);
}
