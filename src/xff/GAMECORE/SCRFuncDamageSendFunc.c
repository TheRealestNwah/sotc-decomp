typedef union {
    struct { float x, y, z, w; } v;
    int i[4];
} __attribute__((aligned(16))) Vec4;

typedef int u128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GetScriptAnimationGlobalBaseInfo(void);
extern char *getSCRDataCtrlWork(void *);
extern int nico_GetPlayerCharacterRidingHorseObject(int);
extern int SCRGetFirstObj(void *);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern long GetGeometryPointerCharColAttr(void *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern void SendDamageLetter(int, int, char *, Vec4 *);

static inline float distanceXYZ(void *a, void *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2", "memory");
    return len;
}

#define CHECK_ATTR(attr, mask, val, m)     ((mask) == -1 || (((m) = (mask) & (attr)) != 0 && (val) == -1) || (m) == (val))

static inline int getTargetPos(int obj, Vec4 *pos, long mask, long val)
{
    char *l = GetLayoutClass(obj);
    char *c = GetCharacterClass(obj);

    if (*(int *)(l + 0x124) != 0) {
        long attr = GetGeometryPointerCharColAttr(l + 0xC0);
        long m;
        if ((int)(attr & 1) != 0 && CHECK_ATTR(attr, mask, val, m)) {
            GetGeometryPointerPosition(pos, l + 0xC0);
            return 1;
        }
    }
    if (*(int *)(c + 0xFF0) != 0 && *(int *)(c + 0xFF4) != 0) {
        long attr = *GetCollisionDBAttributeAdr(c + 0xFF8);
        long m;
        if (CHECK_ATTR(attr, mask, val, m)) {
            *(u128 *)pos = *(u128 *)(c + 0x1000);
            return 1;
        }
    }
    return 0;
}

void SCRFuncDamageSendFunc(void *obj, int u1, int u2, long mask, long val, int u5, unsigned int *tbl)
{
    Vec4 pos;
    char *info;
    char *w;
    int riding;
    int player;
    int horse;
    char *hl;
    char *pl;
    unsigned int v;
    char *t;
    char *sheet;

    info = GetScriptAnimationGlobalBaseInfo();
    w = getSCRDataCtrlWork(obj);
    riding = nico_GetPlayerCharacterRidingHorseObject(*(int *)(w + 0x4078)) != 0;
    horse = *(int *)(w + 0x4078);
    player = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    hl = *(char **)(w + 0x407C);
    pl = GetLayoutClass(player);
    v = *tbl;
    t = (v & 0x3FFFF) != 0 ? *(char **)((char *)tbl - (v & 0x3FFFF)) : 0;
    sheet = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    if (!riding) {
        if (getTargetPos(horse, &pos, mask, val)) {
            pos.v.w = distanceXYZ(*(void **)(hl + 0x134), &pos) + 2.0f;
            SendDamageLetter(0, *(int *)(info + 8), sheet, &pos);
        }
    }
    if (getTargetPos(player, &pos, mask, val)) {
        if (riding) {
            pos.v.w = distanceXYZ(*(void **)(hl + 0x134), &pos) + 2.0f;
            SendDamageLetter(0, *(int *)(info + 8), sheet, &pos);
        } else {
            pos.v.w = distanceXYZ(*(void **)(pl + 0x134), &pos) + 2.0f;
            SendDamageLetter(0, *(int *)(info + 8), sheet, &pos);
        }
    }
}
