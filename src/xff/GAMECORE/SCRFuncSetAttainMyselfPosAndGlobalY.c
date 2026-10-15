typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void setAttainmentPos(char *, Vec4 *);

void SCRFuncSetAttainMyselfPosAndGlobalY(void *a, float y)
{
    Vec4 p;
    char *w = getSCRDataCtrlWork(a);
    char *l = GetLayoutClass(a);
    p.q = (*(Vec4 **)(l + 0x134))->q;
    p.f[1] = y;
    setAttainmentPos(w, &p);
}
