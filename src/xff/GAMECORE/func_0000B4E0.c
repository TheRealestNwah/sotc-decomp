typedef struct {
    char pad0[0x370];
    short kind;
} CharacterClass;

extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern int *isysGetGroupSrhNext(int *);
extern void _isysDeleteGroup(int, void *, int);
extern void isysAddGroupRelativeWithLinkParam(int, void *, int *, int, int, int);
extern char *GetLayoutClass(int);
extern CharacterClass *GetCharacterClass(int);
extern int SCRGetGetGeometryPointerLegalParentObj(void *);
extern int GetGeometryPointerObject(void *);

typedef struct {
    char p0[0x70];
    long t70;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void *GetScriptPriorityGroup(int);
extern void updatePathInfo(void);
extern void scrRun(void);

static void func_0000AA90(void *group)
{
    int o = 0;
    int done = 0;
    int *g;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        char *lc;

        o = *g;
        lc = GetLayoutClass(o);
        if (lc != 0 && *(int *)(lc + 0x124) != 0) {
            int parent = SCRGetGetGeometryPointerLegalParentObj(lc + 0xC0);
            int *n;

            if (parent == 0)
                continue;
            for (n = g; n != 0; n = isysGetGroupSrhNext(n)) {
                if (*n == parent) {
                    _isysDeleteGroup(o, group, 0);
                    isysAddGroupRelativeWithLinkParam(o, group, n, 1, 0, 0);
                    goto next;
                }
            }
        } else if (done == 0) {
            CharacterClass *cc = GetCharacterClass(o);

            if (cc != 0 && cc->kind == 2) {
                int found = 0;
                int *fn = 0;
                int *n;

                for (n = g; n != 0; n = isysGetGroupSrhNext(n)) {
                    int c = *n;
                    CharacterClass *k = GetCharacterClass(c);
                    char *l;

                    if (k != 0 && (unsigned short)(k->kind - 3) < 2) {
                        found = c;
                        fn = n;
                    } else {
                        l = GetLayoutClass(c);
                        if (l != 0 && *(int *)(l + 0x124) != 0) {
                            k = GetCharacterClass(GetGeometryPointerObject(l + 0xC0));
                            if (k != 0 && k->kind == 4) {
                                found = c;
                                fn = n;
                            }
                        }
                    }
                }
                if (found != 0) {
                    done = 1;
                    _isysDeleteGroup(o, group, 0);
                    isysAddGroupRelativeWithLinkParam(o, group, fn, 1, 0, 0);
                }
            }
        }
    next:;
    }
    if (o != 0)
        isysGroupForExit(o, 0);
}

static void func_0000B4E0(void)
{
    void *group = GetScriptPriorityGroup(4);

    for (;;) {
        func_0000AA90(group);
        updatePathInfo();
        gcGlobalVar.t70 = iosGetTCountExtension();
        scrRun();
    }
}
