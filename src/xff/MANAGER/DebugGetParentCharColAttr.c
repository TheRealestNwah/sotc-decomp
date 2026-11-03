#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
extern int MotRootDyn_XZFIT;
extern int CheckLegalCollisionGP(void *);
extern unsigned long *GetCollisionDBAttributeAdr(void *);

static inline char *GetWork(unsigned char *obj) { switch (obj[8]) { case 9: return (char *)obj + 0x90; case 0x16: return (char *)obj + 0x90; default: return 0; } }

int DebugGetParentCharColAttr(unsigned long *out, unsigned char *obj)
{
    char *w = GetWork(obj);

    *out = 0;
    if (w && *(int *)(w + 0x124)) {
        *out = *(unsigned long *)(w + 0x690);
        if (*(int *)(w + 0x438) == MotRootDyn_XZFIT) {
            char *col = w + 0xAC0;
            if (*(int *)(col + 0x4C) && CheckLegalCollisionGP(col))
                *out = *GetCollisionDBAttributeAdr(col);
        }
        return 1;
    }
    return 0;
}
#endif
