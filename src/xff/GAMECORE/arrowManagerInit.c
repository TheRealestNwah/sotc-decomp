#ifdef NONMATCHING
/* 92 diffs, 7 words short (138 vs 145). First-pass draft from the asm; types are guesses. Initialises the arrow pool (25 nodes of 0xD0 bytes chained into the list at B_00189DFC through the +0xC0 next pointer), computes the largest LayoutObj work size over the four arrow defs (BASE_ARROW, then EXPARROW / SOUNDARROW / HARPOON in that order, + 0x279 each) with an init-param block at sp+0x80, creates a partition of 31 * that size, sets up and starts the ARROW_EXP_HIT LWS and jumps to func_000318E0. The loop and pool are where the missing words are: the Original keeps $s1..$s7/$fp live across setLayoutClassInitParam calls for the repeated args and inlines the first def lookup into the loop prologue. */
typedef struct ArrowNode {
    char pad0[0xC0];
    struct ArrowNode *next;
} ArrowNode;

typedef struct {
    int count;
    ArrowNode *head;
    ArrowNode *tail;
} ArrowList;

typedef struct {
    int f0;
    void *pos;
    void *rot;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
} ArrowInit;

extern int B_00189DF0[3];
extern ArrowList B_00189DFC;
extern ArrowNode B_00188930[];
extern char rootPtn[];
extern char ZeroPoint[];
extern char ZeroVector[];
extern char IdentityQuaternion[];
extern int LayoutObjDef_BASE_ARROW;
extern int LayoutObjDef_BASE_EXPARROW;
extern int LayoutObjDef_BASE_SOUNDARROW;
extern int LayoutObjDef_BASE_HARPOON;
extern int ScriptAnimationObjDef_ARROW_EXP_HIT;
extern int D_0017A978;
extern int B_00189E08;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void setLayoutClassInitParam(void *, char *, void *, int, ArrowInit *);
extern int GetLayoutObjWorkSize(void *);
extern int iosCreatePartition(void *, int);
extern int _SCRSetupLWS(int, int, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern void isysJumpSubThread(void (*)(void), int);
extern void func_000318E0(void);

void arrowManagerInit(void)
{
    char param[0x80];
    ArrowInit ini;
    ArrowList *l;
    ArrowNode *n;
    int i;
    int size;
    int work;

    scrInit(isysGetThisSubThread());
    B_00189DF0[0] = 0;
    B_00189DF0[1] = 0;
    B_00189DF0[2] = 0;
    l = &B_00189DFC;
    l->count = 0;
    l->head = 0;
    l->tail = 0;
    n = B_00188930;
    for (i = 24; i >= 0; i--, n = (ArrowNode *)((char *)n + 0xD0)) {
        if (n != 0) {
            if (l->tail == 0)
                l->head = n;
            else
                l->tail->next = n;
            n->next = 0;
            l->tail = n;
            l->count++;
        }
    }
    ini.f0 = 0;
    ini.pos = ZeroPoint;
    ini.rot = IdentityQuaternion;
    ini.f0C = 0;
    ini.f10 = 0;
    ini.f14 = 0;
    ini.f18 = 0;
    ini.f1C = 1;
    ini.f20 = 0;
    ini.f24 = 0;
    ini.f28 = 0;
    ini.f2C = 1;
    ini.f30 = 0;
    ini.f34 = 0;
    ini.f38 = 0;
    setLayoutClassInitParam(param, "arrow_obj", rootPtn, LayoutObjDef_BASE_ARROW, &ini);
    size = GetLayoutObjWorkSize(param) + 0x279;
    for (i = 0; i < 3; i++) {
        int def;

        if (i == 0)
            def = LayoutObjDef_BASE_EXPARROW;
        else if (i == 1)
            def = LayoutObjDef_BASE_SOUNDARROW;
        else
            def = LayoutObjDef_BASE_HARPOON;
        setLayoutClassInitParam(param, "arrow_obj", rootPtn, def, &ini);
        work = GetLayoutObjWorkSize(param) + 0x279;
        if (size < work)
            size = work;
    }
    D_0017A978 = iosCreatePartition(rootPtn, size * 31);
    B_00189E08 = _SCRSetupLWS(ScriptAnimationObjDef_ARROW_EXP_HIT, 0, ZeroVector, IdentityQuaternion, 0);
    _SCRStartLWS(B_00189E08, -1, 1, 0);
    isysJumpSubThread(func_000318E0, 0);
}
#endif
