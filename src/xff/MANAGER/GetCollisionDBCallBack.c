/* Parked draft: flushes the finder set, then collects collision finders for every group member a
   caller-supplied filter accepts (stopping when the set is full); when the set has a limit, deletes
   the finders a script character class added beyond it. 11 diffs, same size: the Original preloads
   `user` into the filter test's delay slot and uses v1 for the p.limit reloads. A 30-minute
   permuter run found nothing better. */
#ifdef NONMATCHING

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

extern void FlushCollisionFinder(FinderSet *);
extern void DeleteCollisionFinder(FinderSet *, int);
extern int GetScriptCharacterClass(int);
extern int func_0009B6C8(FinderSet *, int, float, float, int, int, void *, int, int, int, int);
extern int func_000ADFC8(void *, Params *, int, int);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);

void GetCollisionDBCallBack(FinderSet *set, int group, int a2, int a3, float f12, int (*filter)(int, int),
                            int t1, int t2, int t3, int user)
{
    char tmp[16];
    Params p;

    p.a2 = a2;
    p.a3 = a3;
    p.t1 = t1;
    p.t2 = t2;
    p.t3 = t3;
    FlushCollisionFinder(set);
    p.limit = set->limit;
    p.f = 0;
    func_000ADFC8(tmp, &p, p.a2, p.a3);
    if (p.limit < 0) {
        int *it;
        int member = 0;
        for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0)) {
            member = *it;
            if (set->count >= set->capacity)
                break;
            if (filter == 0 || filter(member, user) != 0)
                func_0009B6C8(set, member, f12, p.f, p.a2, p.a3, tmp, p.t1, p.t2, p.t3, user);
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
                    int added = func_0009B6C8(set, member, f12, p.f, p.a2, p.a3, tmp, p.t1, p.t2, p.t3, user);
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
