/* Parked draft: adds collision finders for every member of a group, optionally filtered by a
   callback, and (when limit >= 0) deletes the finders again that a script character class
   produced beyond the limit. Parked: 6 diffs, same size. An ok flag for the loop-1 filter check
   and an int-typed zero store into p.f brought it from 20; v1/v0 register pins on both p.limit
   tests brought it from 11. Remaining: the p.f zero store is scheduled after the a3 store
   (original: before), the original loads user in the loop-1 filter-check delay slot instead of
   ok = 1, and the loop-2 user reload is in v0 (original: v1). The same ok flag in loop 2 changes
   the size; moving or laundering the zero or a3 store gives the same or worse. */
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
    *(int *)&p.f = 0;
    p.a3 = a3;
    func_000ADF90(tmp, &p);
    if (({
            register int l __asm__("$3") = p.limit;
            l;
        }) < 0) {
        int *it;
        int member = 0;
        for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0)) {
            member = *it;
            if (set->count >= set->capacity)
                break;
            {
            int ok = 1;
            if (filter != 0)
                ok = filter(member, user);
            if (ok != 0)
                func_0009B690(set, member, f12, p.f, p.a2, p.a3, tmp, p.t1, p.t2, p.t3, user);
            }
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
                    if (({
                            register int l __asm__("$3") = p.limit;
                            register int t __asm__("$2") = l < added;
                            t;
                        }) && GetScriptCharacterClass(member) != 0) {
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
