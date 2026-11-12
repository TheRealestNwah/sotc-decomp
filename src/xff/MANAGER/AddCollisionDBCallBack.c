/* Parked draft: adds collision finders for every member of a group, optionally filtered by a
   callback, and (when limit >= 0) deletes the finders again that a script character class
   produced beyond the limit. Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int count;
    int capacity;
    int limit;
} FinderSet;

extern void DeleteCollisionFinder(FinderSet *, int);
extern int GetScriptCharacterClass(int);
extern int func_0009B6C8(FinderSet *, int, int, int, float, s128, int);
extern void func_000ADFC8(void *, s128 *);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);

void AddCollisionDBCallBack(FinderSet *set, int group, int a2, int a3, float f12, int (*filter)(int, int),
                            int t1, int t2, int t3, int user)
{
    char tmp[16] __attribute__((aligned(16)));
    s128 q __attribute__((aligned(16)));
    int sp24 = a2;
    int sp28 = a3;
    int limit = set->limit;
    int *it;
    int member;

    q = 0;
    func_000ADFC8(tmp, &q);
    if (limit < 0) {
        it = isysGroupForFirst(group, 0);
        member = 0;
        while (it != 0) {
            member = *it;
            if (set->count >= set->capacity)
                break;
            if (filter == 0 || filter(member, user) != 0)
                func_0009B6C8(set, member, sp24, sp28, f12, q, user);
            it = isysGroupForNext(it, 0);
        }
        if (member != 0)
            isysGroupForExit(member, 0);
    } else {
        it = isysGroupForFirst(group, 0);
        member = 0;
        if (it != 0) {
            do {
                member = *it;
                if (filter == 0 || filter(member, user) != 0) {
                    int before = set->count < set->capacity ? set->count : -1;
                    int added = func_0009B6C8(set, member, sp24, sp28, f12, q, user);
                    if (limit < added && GetScriptCharacterClass(member) != 0) {
                        int cur = set->count;
                        int i = before;
                        int n = 0;
                        int end = set->capacity < cur ? set->capacity : cur;
                        if (added > 0 && before < end) {
                            do {
                                int idx = i;
                                i++;
                                n++;
                                DeleteCollisionFinder(set, idx);
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
