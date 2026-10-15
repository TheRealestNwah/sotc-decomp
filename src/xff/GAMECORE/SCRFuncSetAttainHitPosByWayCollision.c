typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern int getHitPosWayCollision(char *, Vec4 *, int, float);
extern void setAttainmentPos(char *, Vec4 *);

void SCRFuncSetAttainHitPosByWayCollision(void *a, float r)
{
    Vec4 p;
    char *w = getSCRDataCtrlWork(a);
    if (getHitPosWayCollision(w, &p, *(int *)(*(char **)(w + 0x407C) + 0x134), r))
        setAttainmentPos(w, &p);
}
