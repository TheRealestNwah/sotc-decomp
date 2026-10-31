typedef int s128 __attribute__((mode(TI)));
typedef struct {
    char p0[0x2B8];
    char bossGroup[4];
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern s128 ZeroPoint;
extern void *isysGroupForFirst(void *, int);
extern void isysGroupForExit(void *, int);
extern void *isysGroupForNext(void *, int);
extern int bossStatBootChk(void);
extern char *GetCharacterClass(void *);
extern int GetSkeletonFocusNode(void *);
extern int GAMEUTIL_get_node_posi_by_id(s128 *, void *, int);

static int func_0000A898(s128 *out)
{
    void **it;
    void *obj = 0;
    void *boss = 0;
    int ok;
    int st;

    for (it = isysGroupForFirst(gcGlobalVar.bossGroup, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        boss = obj;
        break;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    if (boss != 0) {
        st = bossStatBootChk();
        ok = st > 0;
        if (st > 0) {
            if (GAMEUTIL_get_node_posi_by_id(out, boss,
                    GetSkeletonFocusNode(*(char **)(GetCharacterClass(boss) + 0x750) + 0x14)) == ok) {
                return ok;
            }
        }
    }
    *out = ZeroPoint;
    return 0;
}
