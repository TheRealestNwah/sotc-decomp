/* Parked draft: adds collision finders for every member of a group, optionally filtered by a
   callback, and (when limit >= 0) deletes the finders again that a script character class
   produced beyond the limit. ~20 diffs, same size: only scheduling left (the zero store into p.f is
   hoisted, user is not preloaded in the filter-check delay slot, and the p.limit reload order).
   Permuter queued. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int count;
    int capacity;
    int limit;
} FinderSet;

typedef struct {
    float f;
    int a2;
    int a3;
    int t1;
    int t2;
    int t3;
    int limit;
} Params;

extern void DeleteCollisionFinder(FinderSet *, int);
extern int GetScriptCharacterClass(int);
extern int func_0009B690(FinderSet *, int, float, float, int, int, void *, int, int, int, int);
extern void func_000ADF90(void *, Params *);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);

void AddCollisionDBCallBack(FinderSet *set, int group, int a2, int a3, float f12, int (*filter)(int, int),
                            int t1, int t2, int t3, int user)
{
    char tmp[16];
    Params p;

    p.limit = set->limit;
    p.t1 = t1;
    p.t2 = t2;
    p.t3 = t3;
    p.a2 = a2;
    p.f = 0;
    p.a3 = a3;
    func_000ADF90(tmp, &p);
    if (p.limit < 0) {
        int *it;
        int member = 0;
        for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0)) {
            member = *it;
            if (set->count >= set->capacity)
                break;
            if (filter == 0 || filter(member, user) != 0)
                func_0009B690(set, member, f12, p.f, p.a2, p.a3, tmp, p.t1, p.t2, p.t3, user);
        }
        if (member != 0)
            isysGroupForExit(member, 0);
    } else {
        int *it = isysGroupForFirst(group, 0);
        int member = 0;
        if (it != 0) {
            do {
                member = *it;
                if (filter == 0 || filter(member, user) != 0) {
                    int before = set->count < set->capacity ? set->count : -1;
                    int added = func_0009B690(set, member, f12, p.f, p.a2, p.a3, tmp, p.t1, p.t2, p.t3, user);
                    if (p.limit < added && GetScriptCharacterClass(member) != 0) {
                        int cur = set->count;
                        int i = before;
                        int n = 0;
                        int end = set->capacity < cur ? set->capacity : cur;
                        if (added > 0 && before < end) {
                            do {
                                DeleteCollisionFinder(set, i);
                                i++;
                                n++;
                            } while (n < added && i < end);
                        }
                        set->count = before;
                    }
                }
                it = isysGroupForNext(it, 0);
            } while (it != 0);
        }
        if (member != 0)
            isysGroupForExit(member, 0);
    }
}
#endif
