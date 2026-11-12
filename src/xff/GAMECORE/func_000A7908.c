typedef struct { long long v[4]; } P32;

extern char gcGlobalVar[];
extern float RO_0017FCE8;
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern char *GetScriptCharacterClass(int);
extern int AI_PlayerParentFlag(int, int);
extern char *getSObjNode(int);
extern void setSObjNodeLock(void *, int);
extern int Kite_CmpPathPoint(void *, void *);
extern void Kite_SucceedKitePathWork(void *, void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int *, int);
extern void iosFree(int);
extern void func_000A7630(char *);

#ifdef NONMATCHING /* 115 diffs, same word count: branch-likely vs plain branch forms and delay-slot fills */
void func_000A7908(char *o)
{
    int thr = isysGetThisSubThread();
    char *lay, *chr, *node, *a0, *a2, *t;
    int s4, s2, *e;

    if (*(int *)o == 6)
        return;
    if (*(int *)(o + 0x26C) < 0x12 && AI_PlayerParentFlag(thr, *(int *)(o + 0x24))) {
        if (*(int *)(o + 0x40) == 0) {
            lay = GetLayoutClass(thr);
            node = getSObjNode(thr);
            if (node)
                setSObjNodeLock(node, 1);
            if (*(long long *)(o + 0x38) == (0x8C00LL << 22))
                func_000A7630(o);
            *(int *)(o + 0x3C) = 0x24;
            *(float *)(o + 0x7A0) = *(float *)(*(char **)(lay + 0x134) + 4) - *(float *)(*(char **)(o + 0x20) + 0xF4);
            *(float *)(o + 0x79C) = *(float *)(*(char **)(lay + 0x134) + 4);
        }
        *(int *)(o + 0x44) = 1;
        *(int *)(o + 0x40) = 1;
    } else {
        chr = GetCharacterClass(thr);
        if (*(int *)(o + 0x40) != 0) {
            node = getSObjNode(thr);
            if (node)
                setSObjNodeLock(node, 0);
        }
        *(int *)(o + 0x40) = 0;
        *(float *)(o + 0x79C) = RO_0017FCE8;
        if (*(int *)(o + 0x44) != 0 && *(int *)(chr + 0xE20) == 0)
            *(int *)(o + 0x44) = 0;
        if (*(int *)(o + 0x3C) == 0x24) {
            if (*(int *)(o + 0x28) == 0) {
                *(int *)(o + 0x3C) = 0x22;
            } else {
                a0 = *(char **)(o + 0x2C);
                if (a0 == 0) {
                    *(int *)(o + 0x3C) = 0x22;
                } else if (Kite_CmpPathPoint(a0 + 0x600, o + 0x600)) {
                    *(P32 *)(o + 0x620) = *(P32 *)(a0 + 0x620);
                    *(P32 *)(o + 0x660) = *(P32 *)(a0 + 0x660);
                    *(int *)(o + 0x3C) = 0x23;
                    s4 = isysGetThisSubThread();
                    if (*(int *)(o + 8) != -1) {
                        s2 = 0;
                        for (e = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); e; e = isysGroupForNext(e, 0)) {
                            s2 = *e;
                            t = *(char **)(GetScriptCharacterClass(s2) + 0x1200);
                            if (t == 0)
                                continue;
                            if (*(int *)t != 1)
                                continue;
                            if (*(int *)(t + 8) != *(int *)(o + 8))
                                continue;
                            if (*(int *)(t + 4) != *(int *)(o + 4))
                                continue;
                            if (*(int *)(t + 0x3C) == 0x24)
                                continue;
                            if (*(int *)(t + 0x26C) >= 0x12)
                                continue;
                            s4 = s2;
                            break;
                        }
                        if (s2 != 0)
                            isysGroupForExit((int *)s2, 0);
                    }
                    if (s4 == thr) {
                        *(int *)(o + 0x28) = thr;
                        *(int *)(o + 0x3C) = 0x22;
                        *(int *)(o + 0x38) = 1;
                        *(char **)(o + 0x2C) = o;
                    } else {
                        Kite_SucceedKitePathWork(o + 0x370, *(char **)(o + 0x2C) + 0x370);
                        if (*(int *)(o + 0x374) >= 0 && *(int *)(o + 0x360) != 0) {
                            iosFree(*(int *)(o + 0x360));
                            *(int *)(o + 0x360) = 0;
                        }
                    }
                }
            }
        }
    }
    if (*(int *)o != 8 && *(int *)(o + 0x584) == 0) {
        a2 = *(char **)(o + 0x2C);
        if (a2 != 0) {
            *(P32 *)(o + 0x620) = *(P32 *)(a2 + 0x620);
            *(P32 *)(o + 0x660) = *(P32 *)(a2 + 0x660);
            Kite_SucceedKitePathWork(o + 0x370, a2 + 0x370);
        }
    }
}
#endif
