typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern void setAttainmentPos(void *, Vec4 *);

void SCRFuncSetAttainPlayerPosAndGlobalY(void *actor, float y)
{
    char *w = getSCRDataCtrlWork(actor);
    Vec4 t;
    t.q = (*(Vec4 **)(*(char **)(w + 0x407C) + 0x134))->q;
    t.f[1] = y;
    setAttainmentPos(w, &t);
}
