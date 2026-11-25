/* Parked: 10 diffs, same size. Resets the player's grip/hang/slip script-control statuses, re-sets the hand-slip flags on an EDGEXZ root, then sums func_00090560 over the four attribute slots at B_0018B748 (after func_000910B0 when the animation has a resolved hang table), sets the grip statuses from the result, runs the fall-down hang search (func_000906D8 / func_00090F28) in the falling control modes, and relinks the layout's geometry pointer. The second loop's running result is pinned to v0, as in the Original. Remaining: v0/v1 swap on the B_0018B748 address and the ControlMode compare, and the second loop's setup order (the Original computes work + 0x70 before zeroing v0). */
#ifdef NONMATCHING
typedef struct { char pad[0x18]; } AttrSt;
typedef struct { int pad0; int id; } ScriptCtrlDef;
extern AttrSt B_0018B748[];
extern int DldSysUndefSymbol;
extern int MotRootDyn_EDGEXZ;
extern int ControlMode_PLAYER_FALL;
extern int ControlMode_PLAYER_JUMP;
extern int ControlMode_PLAYER_RUN_FALL;
extern int ControlMode_PLAYER_TUMBLE_FALL;
extern int ControlMode_PLAYER_HANG_AFTER_FALL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerEdgeGripSub;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerHandGripSub;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerUpDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerDownDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerRightDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerLeftDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerFrontDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerBackDirectionHang;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerRHandSlipEdge;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerLHandSlipEdge;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerRDirectSlip;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerLDirectSlip;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerFDirectSlip;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerBDirectSlip;
extern void CharaCtrlResetScriptCtrlStatus(void *, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern char *GetCharacterClass(void *);
extern char **GetAnimationClass(void *);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void CopyGeometryPointer(void *, void *);
extern void DeleteTwoWayLink(void *);
extern void AddTwoWayLinkNext(void *, void *);
static int func_00090560(AttrSt *, void *, void *, int, void *);
static int func_000910B0(void *, void *, void *, char *, int);
static int func_000906D8(void *, void *, void *, char *, void *);
static void func_00090F28(void *, void *, void *, void *);

static inline char *dldResolve(unsigned int *h, unsigned int v)
{
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int dldCount(unsigned int *h, unsigned int v)
{
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

void player_updateAttrStatusAndFindHangPosWithFallDown(void *obj, char *work, int noFall)
{
    char a[16];
    char b[16];
    char *cc;
    char *anim;
    char *lc;
    int done;
    int i;
    int r;
    AttrSt *p;

    *(int *)(work + 0x60) = 0;
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerEdgeGripSub->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerHandGripSub->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerUpDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerDownDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerRightDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerLeftDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerFrontDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerBackDirectionHang->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerRHandSlipEdge->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerLHandSlipEdge->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerRDirectSlip->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerLDirectSlip->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerFDirectSlip->id);
    CharaCtrlResetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerBDirectSlip->id);
    cc = GetCharacterClass(obj);
    if (*(int *)(cc + 0x438) == MotRootDyn_EDGEXZ) {
        if (cc[0xA94] == 0)
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerRHandSlipEdge->id);
        if (cc[0xA95] == 0)
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerLHandSlipEdge->id);
    }
    anim = *GetAnimationClass(obj);
    done = 0;
    if (anim != 0) {
        unsigned int *h = (unsigned int *)(anim + 0x14);
        unsigned int v = *h;
        char *res = dldResolve(h, v);
        if (res != 0) {
            *(int *)(work + 0x60) = func_000910B0(work + 0x70, work + 0xB0, obj, res, dldCount(h, v));
            r = 0;
            p = B_0018B748;
            i = 4;
            do {
                r = func_00090560(p++, 0, 0, r, obj);
            } while (--i);
            done = 1;
        }
    }
    if (!done) {
        register int r2 asm("$2") = 0;
        AttrSt *q = B_0018B748;
        int k;
        k = 4;
        do {
            r2 = func_00090560(q, work + 0x70, work + 0xB0, r2, obj);
            q++;
            k--;
        } while (k);
        *(int *)(work + 0x60) = r2;
    }
    if (*(int *)(work + 0x60) & 1)
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerEdgeGripSub->id);
    if (*(int *)(work + 0x60) & 2)
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerHandGripSub->id);
    if (*(int *)(work + 0x60) == 0 && noFall == 0) {
        int mode;
        int hit;
        char *c2 = GetCharacterClass(obj);
        mode = *(int *)(c2 + 0x750);
        hit = 0;
        if (mode == ControlMode_PLAYER_FALL || mode == ControlMode_PLAYER_JUMP || mode == ControlMode_PLAYER_RUN_FALL
            || mode == ControlMode_PLAYER_TUMBLE_FALL || mode == ControlMode_PLAYER_HANG_AFTER_FALL)
            hit = func_000906D8(a, b, obj, c2, work);
        if (hit)
            func_00090F28(obj, work, a, b);
    }
    lc = GetLayoutClass(obj);
    if (*(int *)(lc + 0x124) != 0) {
        char *geo = lc + 0xC0;
        if (*(int *)work != 0) {
            *(int *)work = 0;
            DeleteTwoWayLink(work + 0x50);
        }
        *(int *)work = 1;
        CopyGeometryPointer(work + 0x10, geo);
        AddTwoWayLinkNext(GetLayoutClass(GetGeometryPointerObject(geo)) + 0x118, work + 0x50);
    }
}
#endif
